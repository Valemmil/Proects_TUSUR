document.addEventListener('DOMContentLoaded', function(){
  document.querySelector("body").onmousemove = function(event) {
      event = event || window.event; // кроссбраузерность
      document.querySelector('.x').innerHTML = event.offsetX;
      document.querySelector('.y').innerHTML = event.offsetY;
  }
}, false)