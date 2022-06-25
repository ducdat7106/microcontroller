const char webpage_my[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>

  <head>
    <meta charset="utf-8"> 
  </head>


  <style>
  
  </style>


  <script>
  
    function DK_DEN()
    {
      //hiển thị để xem hàm có chạy hay không
      console.log("Button đèn onclick!!!");
      
      var xhttp = new XMLHttpRequest();
      xhttp.open("GET", "/onclickden", true);
      xhttp.send();
    }
    
    // http://192.168.1.80:80/onclickden
    
    function DK_QUAT()
    {
      console.log("Button quạt onclick!!!");
      var xhttp = new XMLHttpRequest();
      xhttp.open("GET", "/onclickquat", true);
      xhttp.send();
    }
    
    function SEND_C1()
    {
      //send dữ liệu xuống
      console.log("Button CÀI ĐẶT 1 onclick!!!");
    }
    
    function SEND_C2()
    {
      console.log("Button CÀI ĐẶT 2 onclick!!!");
    }
    
    function UpdateData()
    {
      var xhttp = new XMLHttpRequest();
      // viết hàm nhận dữ liệu response
      xhttp.onreadystatechange = function ()
      {
          // nếu có this.readyState == 4 && this.status == 200
        if(this.readyState == 4 && this.status == 200)
        {
          var DataVDK = xhttp.responseText;
          console.log("Dữ liệu VDK: " + DataVDK);
          //{"ND":"3059","DA":"6118.00","TB1":"1","TB2":"0","C1":"500","C2":"1000","C3":"300"}
          var DataJson = JSON.parse(DataVDK); 
          
          if(DataJson.ND != null)
          {
            document.getElementById("nhietdo").innerHTML = DataJson.ND;
          }
          
          if(DataJson.DA != null)
          {
            document.getElementById("doam").innerHTML = DataJson.DA;
          }
          
          if(DataJson.C1 != null)
          {
            document.getElementById("cai1").innerHTML = DataJson.C1;
          }
          
          if(DataJson.C2 != null)
          {
            document.getElementById("cai2").innerHTML = DataJson.C1;
          }
          
          if(DataJson.C3 != null)
          {
            document.getElementById("cai3").innerHTML = DataJson.C3;
          }
          
          if(DataJson.TB1 != null)
          {
            //document.getElementById("cai3").innerHTML = DataJson.C3;
            
            if(DataJson.TB1 == 0)
            {
              document.getElementById("trangthaiden").innerHTML = "OFF";
              document.getElementById("nutnhan").innerHTML = "OFF";
            }
            else if(DataJson.TB1 == 1)
            {
              document.getElementById("trangthaiden").innerHTML = "ON";
              document.getElementById("nutnhan").innerHTML = "ON";
            }
            
          }
          
          
          if(DataJson.TB2 != null)
          {
            //document.getElementById("cai3").innerHTML = DataJson.C3;
            
            if(DataJson.TB2 == 0)
            {
              document.getElementById("trangthaiquat").innerHTML = "OFF";
            }
            else if(DataJson.TB2 == 1)
            {
              document.getElementById("trangthaiquat").innerHTML = "ON";
            }
            
          }          
        }
      }     
      
      xhttp.open("GET", "/LoadData", true);
      xhttp.send();
      setTimeout(function(){ UpdateData() }, 1000);
    }
  </script>


<body onload = "UpdateData()">

<h1>Webserver!!!</h1>

<h1>
  ĐÈN
  <button  onclick="DK_DEN()">ĐÈN</button>
</h1>

<h1>
  QUẠT
  <button onclick="DK_QUAT()">QUẠT</button>
</h1>

<h1>
  CÀI ĐẶT 1:
  <input></input>
  <button onclick="SEND_C1()">Send</button>
</h1>

<h1>
  CÀI ĐẶT 2:
  <input></input>
  <button onclick="SEND_C2()">Send</button>
</h1>


<h1>
  NHIỆT ĐỘ:
  <label id="nhietdo">0<label>
</h1>

<h1>
  ĐỘ ẨM:
  <label id="doam">0<label>
</h1>

<h1>
  CÀI ĐẶT 1:
  <label id="cai1">0<label>
</h1>

<h1>
  CÀI ĐẶT 2:
  <label id="cai2">0<label>
</h1>

<h1>
  CÀI ĐẶT 2:
  <label id="cai3">0<label>
</h1>


<h1>
  TRẠNG THÁI ĐÈN:
  <label id="trangthaiden">OFF<label>
</h1>


<h1>
  TRẠNG THÁI QUẠT:
  <label id="trangthaiquat">OFF<label>
</h1>


</body>

</html>

)=====";
