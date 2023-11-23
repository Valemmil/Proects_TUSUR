using System.Text.RegularExpressions;

void main(){
    string reg = File.ReadAllText("regex.txt");
    string text = File.ReadAllText("input.txt");

    string result = regexSearch(reg, text);

    File.WriteAllText("out.txt", result);
}

string regexSearch(string reg, string text){
    Regex regex = new(reg, RegexOptions.IgnorePatternWhitespace | RegexOptions.Multiline);

    MatchCollection matches = regex.Matches(text);

    HashSet<string> vars = new();
    foreach (Match match in matches.Cast<Match>())
        for (int i = 0; i < match.Groups.Count; i++)
            for (int j = 0; j < match.Groups[i].Captures.Count; j++){
                int index = match.Groups[i].Captures[j].Index;
                string[] lines = text[..index].Split('\n');

                if (match.Groups[i].Name == "id"){
                    if (!vars.Add(match.Groups[i].Captures[j].Value))
                        return $"Тип ошибки:\nID_en_double\nРасположение ошибки:\n{lines.Length}:{lines[^1].Length+1}\n"
                        + $"Содержание ошибки:\n{match.Groups[i].Captures[j].Value}\n";
                    continue;
                }

                if (match.Groups[i].Name.Length >= 5 && match.Groups[i].Name[..5] == "error"){
                    return $"Тип ошибки:\n{match.Groups[i].Name}\nРасположение ошибки:\n{lines.Length}:{lines[^1].Length+1}\n"
                        + $"Содержание ошибки:\n{match.Groups[i].Captures[j].Value}\n";
                }
            }
    
    return "Описание корректно";
}

main();