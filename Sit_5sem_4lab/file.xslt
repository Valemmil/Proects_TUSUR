<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version = "1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="/">
  <html>
    <head>
      <link href="style.css" rel="stylesheet"/>
      <title>Posion mouse</title>
    </head>
    <body>
      <p>Welcom!</p>
      <form>
        <lable>Name: </lable>
        <input type="text" id="name" name="name"/>
        <input type="submit" id="submit_form" name="submit_form"/>
      </form>
      X: <span class = "x">0</span>
      <br/>
      Y: <span class = "y">0</span>
      <br/>
      <script type="text/javascript">
        document.addEventListener('DOMContentLoaded', function(){
          const submitFormButton = document.querySelector("#submit_form");

          let websocketClient = new WebSocket("ws://localhost:5000");

          websocketClient.onopen = function() {
            console.log("Client connected!");
          }

          document.querySelector("body").onmousemove = function(event) {
              event = event || window.event;
              document.querySelector('.x').innerHTML = event.offsetX;
              document.querySelector('.y').innerHTML = event.offsetY;
          }

        }, false)
      </script>
    </body>
  </html>
</xsl:template>
</xsl:stylesheet>
