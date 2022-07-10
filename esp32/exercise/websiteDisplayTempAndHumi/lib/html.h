/* static const char MAIN_page[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en">
    <head>
        <title>Lập trình esp32 hiển thị nhiệt độ, độ ẩm</title>
        <meta charset="utf-8"> <!--hỗ trợ tiếng việt-->
        <link rel="stylesheet" href="main_1.css">
    </head>

    
    <body>
       <div>
            Nhiệt độ : <span id="nhietdos">0</span>°C<br/>
            Độ Ẩm : <span id = "doams">0</span>%<br/>
       </div>

       <script>
            setInterval(function()
            {
                // Call a function repetatively with 2 Second interval
                getnhietdo();
                getdoam();
            }, 1000);//1000mSeconds update rate

            function getnhietdo()
            {
                var xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function()
                {
                    if(this.readyState == 4 && this.status==200)
                    {
                        document.getElementById("nhietdos").innerHTML=this.responseText;
                    }
                };
                xhttp.open("GET", "docnhietdo", true);
                xhttp.send();
            }

            function getdoam()
            {
                var xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function()
                {
                    if(this.readyState == 4 && this.status==200)
                    {
                        document.getElementById("doams").innerHTML=this.responseText;
                    }
                };
                xhttp.open("GET", "docdoam", true);
                xhttp.send();
            }
        </script>
    </body>
</html>

)=====";

*/

#include <Arduino.h>

// HTML & CSS contents which display on web server
String  MAIN_page = "<!DOCTYPE html>\
<html>\
<body>\
<h1>My First Web Server with ESP32 - AP Mode &#128522;</h1>\
</body>\
</html>";