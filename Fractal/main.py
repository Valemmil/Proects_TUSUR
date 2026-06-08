import pygame
import math
import sys
from typing import List, Tuple, Dict
from colorsys import hsv_to_rgb


class LSystem:
    def __init__(self, axiom: str, rules: Dict[str, str], angle: float,
                 step_length: float = 2.0, color: Tuple[int, int, int] = (255, 165, 0),
                 bg_color: Tuple[int, int, int] = (0, 0, 0),
                 start_angle: float = 90, line_width: int = 1):
        self.axiom = axiom
        self.rules = rules
        self.angle = angle
        self.step_length = step_length
        self.color = color
        self.bg_color = bg_color
        self.start_angle = start_angle
        self.line_width = line_width

    def generate(self, iterations: int) -> str:
        if iterations == 0:
            return self.axiom
        current = self.axiom
        for _ in range(iterations):
            current = ''.join(self.rules.get(ch, ch) for ch in current)
        return current

    def generate_points(self, instructions: str) -> List[List[Tuple[float, float]]]:
        segments = []
        current_segment = []
        x, y = 0.0, 0.0
        heading = math.radians(self.start_angle)
        stack = []
        current_segment.append((x, y))

        for cmd in instructions:
            if cmd == 'F':
                x += self.step_length * math.cos(heading)
                y += self.step_length * math.sin(heading)
                current_segment.append((x, y))
            elif cmd == 'S':
                if len(current_segment) > 1:
                    segments.append(current_segment)
                x += self.step_length * math.cos(heading)
                y += self.step_length * math.sin(heading)
                current_segment = [(x, y)]
            elif cmd == '+':
                heading += math.radians(self.angle)
            elif cmd == '-':
                heading -= math.radians(self.angle)
            elif cmd == '[':
                stack.append((x, y, heading))
            elif cmd == ']':
                if stack:
                    if len(current_segment) > 1:
                        segments.append(current_segment)
                    x, y, heading = stack.pop()
                    current_segment = [(x, y)]

        if len(current_segment) > 1:
            segments.append(current_segment)
        return segments

    def compute_bounds(self, points: List[List[Tuple[float, float]]]) -> Tuple[float, float, float, float]:
        min_x = min_y = float('inf')
        max_x = max_y = float('-inf')
        for segment in points:
            for x, y in segment:
                min_x = min(min_x, x)
                max_x = max(max_x, x)
                min_y = min(min_y, y)
                max_y = max(max_y, y)
        return min_x, max_x, min_y, max_y


class Slider:
    """Простой горизонтальный слайдер для Pygame."""
    def __init__(self, x, y, w, h, min_val, max_val, start_val, label=""):
        self.rect = pygame.Rect(x, y, w, h)
        self.min = min_val
        self.max = max_val
        self.value = start_val
        self.label = label
        self.dragging = False
        self.handle_radius = h // 2

    def handle_event(self, event):
        if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            if self.rect.collidepoint(event.pos):
                self.dragging = True
        elif event.type == pygame.MOUSEBUTTONUP:
            self.dragging = False
        elif event.type == pygame.MOUSEMOTION and self.dragging:
            rel_x = event.pos[0] - self.rect.x
            rel_x = max(0, min(self.rect.width, rel_x))
            self.value = self.min + (rel_x / self.rect.width) * (self.max - self.min)
            # Для целых значений
            if isinstance(self.min, int) and isinstance(self.max, int):
                self.value = int(round(self.value))

    def draw(self, screen, font):
        # Track
        pygame.draw.rect(screen, (80, 80, 80), self.rect)
        # Handle
        handle_x = self.rect.x + (self.value - self.min) / (self.max - self.min) * self.rect.width
        pygame.draw.circle(screen, (200, 200, 200), (int(handle_x), self.rect.centery), self.handle_radius)
        # Label
        text = font.render(f"{self.label}: {self.value:.2f}" if isinstance(self.value, float) else f"{self.label}: {self.value}", True, (255, 255, 255))
        screen.blit(text, (self.rect.x, self.rect.y - 20))


class FractalViewer:
    def __init__(self, width: int = 1024, height: int = 768):
        pygame.init()
        self.width = width
        self.height = height
        self.screen = pygame.display.set_mode((width, height), pygame.RESIZABLE)
        pygame.display.set_caption(
            "L-System Lab | 1-5: пресеты | C: цвет по глубине | V: SVG | H: HQ PNG | R: сброс | Esc: выход"
        )
        self.clock = pygame.time.Clock()
        self.font = pygame.font.Font(None, 24)
        self.offset_x = 0.0
        self.offset_y = 0.0
        self.scale = 1.0
        self.min_scale = 0.001
        self.max_scale = 1000.0
        self.dragging = False
        self.last_mouse_pos = None
        self.segments = None
        self.bounds = None
        self.iterations = 3
        self.instructions_count = 0
        self.use_color_depth = False

        # Слайдеры (левая панель)
        slider_x = 10
        slider_w = 150
        self.sliders = {
            "iterations": Slider(slider_x, 60, slider_w, 10, 0, 16, self.iterations, "Итерации"),
            "angle": Slider(slider_x, 110, slider_w, 10, 0, 180, 90, "Угол"),
            "step": Slider(slider_x, 160, slider_w, 10, 1, 20, 2, "Шаг"),
            "width": Slider(slider_x, 210, slider_w, 10, 1, 10, 1, "Толщина"),
        }
        self.update_params_from_sliders()

    def update_params_from_sliders(self):
        self.iterations = int(self.sliders["iterations"].value)
        self.angle = self.sliders["angle"].value
        self.step_length = self.sliders["step"].value
        self.line_width = int(self.sliders["width"].value)

    def setup_fractal(self, l_system: LSystem):
        instructions = l_system.generate(self.iterations)
        self.instructions_count = len(instructions)
        if self.use_color_depth:
            self.segments = self._generate_colored_segments(instructions, l_system)
        else:
            self.segments = l_system.generate_points(instructions)
        self.bounds = l_system.compute_bounds(self.segments)
        self.reset_view()

    def _generate_colored_segments(self, instructions, l_system):
        """Генерирует сегменты с цветом в зависимости от глубины стека."""
        colored_segments = []  # (color, segment)
        current_segment = []
        x, y = 0.0, 0.0
        heading = math.radians(l_system.start_angle)
        stack = []
        depth = 0
        max_depth = 0
        current_segment.append((x, y, depth))

        for cmd in instructions:
            if cmd == 'F':
                x += l_system.step_length * math.cos(heading)
                y += l_system.step_length * math.sin(heading)
                current_segment.append((x, y, depth))
            elif cmd == 'S':
                if len(current_segment) > 1:
                    colored_segments.append((depth, current_segment.copy()))
                x += l_system.step_length * math.cos(heading)
                y += l_system.step_length * math.sin(heading)
                current_segment = [(x, y, depth)]
            elif cmd == '+':
                heading += math.radians(l_system.angle)
            elif cmd == '-':
                heading -= math.radians(l_system.angle)
            elif cmd == '[':
                stack.append((x, y, heading, depth))
                depth += 1
                max_depth = max(max_depth, depth)
            elif cmd == ']':
                if stack:
                    if len(current_segment) > 1:
                        colored_segments.append((depth, current_segment.copy()))
                    x, y, heading, depth = stack.pop()
                    current_segment = [(x, y, depth)]

        if len(current_segment) > 1:
            colored_segments.append((depth, current_segment))

        # Преобразуем в обычный формат сегментов + список цветов
        self.color_map = {}
        segments = []
        colors = []
        for d, seg in colored_segments:
            pure_seg = [(p[0], p[1]) for p in seg]
            segments.append(pure_seg)
            # Цвет по HSV: оттенок зависит от глубины
            hue = (d / max(1, max_depth)) * 0.8  # от 0 до 0.8 (синий-красный)
            r, g, b = hsv_to_rgb(hue, 0.9, 1.0)
            colors.append((int(r * 255), int(g * 255), int(b * 255)))
        self.segment_colors = colors
        return segments

    def reset_view(self):
        if not self.bounds or not self.segments:
            return
        min_x, max_x, min_y, max_y = self.bounds
        width_range = max_x - min_x or 1
        height_range = max_y - min_y or 1
        scale_x = (self.width * 0.7) / width_range  # оставляем место под слайдеры
        scale_y = (self.height * 0.9) / height_range
        self.scale = min(scale_x, scale_y)
        center_x = (min_x + max_x) / 2
        center_y = (min_y + max_y) / 2
        self.offset_x = self.width * 0.55 - center_x * self.scale
        self.offset_y = self.height / 2 - center_y * self.scale

    def world_to_screen(self, wx: float, wy: float) -> Tuple[int, int]:
        sx = int(wx * self.scale + self.offset_x)
        sy = int(wy * self.scale + self.offset_y)
        return sx, sy

    def screen_to_world(self, sx: int, sy: int) -> Tuple[float, float]:
        wx = (sx - self.offset_x) / self.scale
        wy = (sy - self.offset_y) / self.scale
        return wx, wy

    def zoom(self, factor: float, mouse_x: int = None, mouse_y: int = None):
        self.scale *= factor
        self.scale = max(self.min_scale, min(self.max_scale, self.scale))
        if mouse_x is not None and mouse_y is not None:
            wx, wy = self.screen_to_world(mouse_x, mouse_y)
            self.offset_x = mouse_x - wx * self.scale
            self.offset_y = mouse_y - wy * self.scale
        else:
            center_x, center_y = self.width / 2, self.height / 2
            wx, wy = self.screen_to_world(center_x, center_y)
            self.offset_x = center_x - wx * self.scale
            self.offset_y = center_y - wy * self.scale

    def draw_fractal(self, l_system: LSystem):
        if not self.segments:
            return
        if self.use_color_depth and hasattr(self, 'segment_colors'):
            for i, segment in enumerate(self.segments):
                if len(segment) < 2:
                    continue
                color = self.segment_colors[i]
                screen_points = [self.world_to_screen(x, y) for x, y in segment]
                pygame.draw.lines(self.screen, color, False, screen_points, l_system.line_width)
        else:
            for segment in self.segments:
                if len(segment) < 2:
                    continue
                screen_points = [self.world_to_screen(x, y) for x, y in segment]
                pygame.draw.lines(self.screen, l_system.color, False, screen_points, l_system.line_width)

    def draw_info(self, l_system: LSystem):
        info_lines = [
            f"Итераций: {self.iterations}",
            f"Инструкций: {self.instructions_count:,}",
            f"Масштаб: {self.scale:.4f}",
            f"Сегментов: {len(self.segments)}",
            "1-5: пресеты | C: цвет",
            "V: SVG | H: HQ PNG",
        ]
        y = self.height - 120
        for line in info_lines:
            text = self.font.render(line, True, (200, 200, 200))
            shadow = self.font.render(line, True, (0, 0, 0))
            self.screen.blit(shadow, (self.width - 250, y + 1))
            self.screen.blit(text, (self.width - 250, y))
            y += 25

    def save_screenshot(self, l_system: LSystem):
        self.screen.fill(l_system.bg_color)
        self.draw_fractal(l_system)
        pygame.display.flip()
        filename = f"fractal_i{self.iterations}_screen.png"
        pygame.image.save(self.screen, filename)
        print(f"Скриншот сохранён: {filename}")

    def render_high_quality(self, l_system: LSystem, output_filename: str,
                            image_width: int, image_height: int):
        if not self.segments:
            return
        min_x, max_x, min_y, max_y = self.bounds
        world_width = max_x - min_x or 1
        world_height = max_y - min_y or 1
        margin = 0.05
        scale_x = (image_width * (1 - 2 * margin)) / world_width
        scale_y = (image_height * (1 - 2 * margin)) / world_height
        scale = min(scale_x, scale_y)
        offset_x = image_width / 2 - (min_x + max_x) / 2 * scale
        offset_y = image_height / 2 - (min_y + max_y) / 2 * scale
        render_surface = pygame.Surface((image_width, image_height))
        render_surface.fill(l_system.bg_color)

        if self.use_color_depth and hasattr(self, 'segment_colors'):
            for i, segment in enumerate(self.segments):
                if len(segment) < 2:
                    continue
                points = [(int(x * scale + offset_x), int(y * scale + offset_y)) for x, y in segment]
                pygame.draw.lines(render_surface, self.segment_colors[i], False, points, max(1, l_system.line_width))
        else:
            for segment in self.segments:
                if len(segment) < 2:
                    continue
                points = [(int(x * scale + offset_x), int(y * scale + offset_y)) for x, y in segment]
                pygame.draw.lines(render_surface, l_system.color, False, points, max(1, l_system.line_width))

        pygame.image.save(render_surface, output_filename)
        print(f"Изображение сохранено: {output_filename} ({image_width}x{image_height})")

    def export_svg(self, l_system: LSystem, filename: str):
        """Экспорт в векторный SVG с текущим масштабом и смещением."""
        if not self.segments:
            return
        with open(filename, 'w') as f:
            f.write(f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {self.width} {self.height}">\n')
            f.write(f'<rect width="100%" height="100%" fill="rgb{l_system.bg_color}"/>\n')
            # Группа с трансформацией (масштаб и смещение)
            f.write(f'<g transform="translate({self.offset_x},{self.offset_y}) scale({self.scale})">\n')
            if self.use_color_depth and hasattr(self, 'segment_colors'):
                for i, segment in enumerate(self.segments):
                    if len(segment) < 2:
                        continue
                    r, g, b = self.segment_colors[i]
                    path = "M " + " L ".join([f"{x},{y}" for x, y in segment])
                    f.write(f'<path d="{path}" fill="none" stroke="rgb({r},{g},{b})" stroke-width="{l_system.line_width / self.scale}"/>\n')
            else:
                path_parts = []
                for segment in self.segments:
                    if len(segment) < 2:
                        continue
                    path = "M " + " L ".join([f"{x},{y}" for x, y in segment])
                    path_parts.append(path)
                full_path = " ".join(path_parts)
                r, g, b = l_system.color
                f.write(f'<path d="{full_path}" fill="none" stroke="rgb({r},{g},{b})" stroke-width="{l_system.line_width / self.scale}"/>\n')
            f.write('</g>\n</svg>')
        print(f"SVG сохранён: {filename}")

    def run(self, l_system: LSystem):
        self.setup_fractal(l_system)
        running = True
        needs_redraw = True

        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False

                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_ESCAPE:
                        running = False
                    elif event.key == pygame.K_r:
                        self.reset_view()
                        needs_redraw = True
                    elif event.key == pygame.K_s:
                        self.save_screenshot(l_system)
                        needs_redraw = True
                    elif event.key == pygame.K_h:
                        print("\n--- HQ Render ---")
                        print("1: Full HD | 2: 4K | 3: 8K или введите W H:")
                        choice = input("> ").strip()
                        if choice == '1': w, h = 1920, 1080
                        elif choice == '2': w, h = 3840, 2160
                        elif choice == '3': w, h = 7680, 4320
                        else:
                            parts = choice.split()
                            if len(parts) == 2 and parts[0].isdigit() and parts[1].isdigit():
                                w, h = int(parts[0]), int(parts[1])
                            else: w, h = 1920, 1080
                        filename = f"fractal_i{self.iterations}_{w}x{h}.png"
                        self.render_high_quality(l_system, filename, w, h)
                        needs_redraw = True
                    elif event.key == pygame.K_v:
                        self.export_svg(l_system, f"fractal_i{self.iterations}.svg")
                    elif event.key == pygame.K_c:
                        self.use_color_depth = not self.use_color_depth
                        self.setup_fractal(l_system)
                        needs_redraw = True
                    elif event.key in (pygame.K_1, pygame.K_2, pygame.K_3, pygame.K_4, pygame.K_5):
                        presets = {
                            pygame.K_1: ("F+F+F+F", {"F": "FF+F+F+F+F+F-F"}, 90, 2, "Квадратный остров"),
                            pygame.K_2: ("F++F++F", {"F": "F-F++F-F"}, 60, 3, "Снежинка Коха"),
                            pygame.K_3: ("A", {"A": "B-A-B", "B": "A+B+A"}, 60, 1, "Треугольник Серпинского"),
                            pygame.K_4: ("X", {"X": "F-[[X]+X]+F[+FX]-X", "F": "FF"}, 25, 2, "Растение"),
                            pygame.K_5: ("FX", {"X": "X+YF+", "Y": "-FX-Y"}, 90, 2, "Dragon curve"),
                        }
                        axiom, rules, angle, step = presets[event.key]
                        l_system.axiom = axiom
                        l_system.rules = rules
                        l_system.angle = angle
                        l_system.step_length = step
                        self.sliders["angle"].value = angle
                        self.sliders["step"].value = step
                        self.update_params_from_sliders()
                        self.setup_fractal(l_system)
                        self.reset_view()
                        needs_redraw = True

                    elif event.key == pygame.K_PLUS or event.key == pygame.K_EQUALS:
                        self.zoom(1.1)
                        needs_redraw = True
                    elif event.key == pygame.K_MINUS:
                        self.zoom(0.9)
                        needs_redraw = True

                elif event.type == pygame.VIDEORESIZE:
                    self.width = event.w
                    self.height = event.h
                    self.screen = pygame.display.set_mode((self.width, self.height), pygame.RESIZABLE)
                    self.reset_view()
                    needs_redraw = True

                elif event.type == pygame.MOUSEBUTTONDOWN:
                    if event.button == 1:
                        # Проверяем, не попали ли в слайдер
                        hit_slider = False
                        for s in self.sliders.values():
                            if s.rect.collidepoint(event.pos):
                                s.handle_event(event)
                                hit_slider = True
                                break
                        if not hit_slider:
                            self.dragging = True
                            self.last_mouse_pos = event.pos
                    elif event.button == 4:
                        self.zoom(1.1, *event.pos)
                        needs_redraw = True
                    elif event.button == 5:
                        self.zoom(0.9, *event.pos)
                        needs_redraw = True

                elif event.type == pygame.MOUSEBUTTONUP:
                    if event.button == 1:
                        self.dragging = False
                        for s in self.sliders.values():
                            s.dragging = False

                elif event.type == pygame.MOUSEMOTION:
                    if self.dragging:
                        dx = event.pos[0] - self.last_mouse_pos[0]
                        dy = event.pos[1] - self.last_mouse_pos[1]
                        self.offset_x += dx
                        self.offset_y += dy
                        self.last_mouse_pos = event.pos
                        needs_redraw = True
                    # Обновляем слайдеры при движении
                    for s in self.sliders.values():
                        s.handle_event(event)

                elif event.type == pygame.MOUSEWHEEL:
                    mouse_pos = pygame.mouse.get_pos()
                    if event.y > 0:
                        self.zoom(1.1, *mouse_pos)
                    else:
                        self.zoom(0.9, *mouse_pos)
                    needs_redraw = True

                # Проверка изменения слайдеров
                old_iters = self.iterations
                old_angle = self.angle
                old_step = self.step_length
                old_width = self.line_width
                self.update_params_from_sliders()
                if (old_iters != self.iterations or old_angle != self.angle or
                    old_step != self.step_length or old_width != self.line_width):
                    l_system.angle = self.angle
                    l_system.step_length = self.step_length
                    l_system.line_width = self.line_width
                    self.setup_fractal(l_system)
                    self.reset_view()
                    needs_redraw = True

            if needs_redraw:
                self.screen.fill(l_system.bg_color)
                self.draw_fractal(l_system)
                # Рисуем слайдеры
                for s in self.sliders.values():
                    s.draw(self.screen, self.font)
                self.draw_info(l_system)
                pygame.display.flip()
                needs_redraw = False

            self.clock.tick(60)

        pygame.quit()
        sys.exit()


if __name__ == '__main__':
    axiom = "F++F++F++F++F"
    rules = {"F":"F++F++F+++++F-F++F"}
    iterations = 2 # TOP: 5
    angle = 36
    
    
    step_length = 2
    line_width = 1
    start_angle = 90
    line_color = (255, 165, 0)
    bg_color = (10, 10, 20)

    lsys = LSystem(
        axiom=axiom,
        rules=rules,
        angle=angle,
        step_length=step_length,
        color=line_color,
        bg_color=bg_color,
        start_angle=start_angle,
        line_width=line_width
    )

    viewer = FractalViewer(width=1024, height=768)
    viewer.run(lsys)
