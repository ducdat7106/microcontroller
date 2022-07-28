  // Import the functions you need from the SDKs you need
  // import { initializeApp } from "https://www.gstatic.com/firebasejs/9.8.1/firebase-app.js";
  // TODO: Add SDKs for Firebase products that you want to use
  // https://firebase.google.com/docs/web/setup#available-libraries

  // Your web app's Firebase configuration
  const firebaseConfig = {
    apiKey: "AIzaSyCeFg0Vnj6TXU-j4VvL-BhwVFkj8negsLE",
    authDomain: "tt-iot-utc.firebaseapp.com",
    databaseURL: "https://tt-iot-utc-default-rtdb.firebaseio.com",
    projectId: "tt-iot-utc",
    storageBucket: "tt-iot-utc.appspot.com",
    messagingSenderId: "457897367163",
    appId: "1:457897367163:web:0ba514c3f54782499fb4de"
  };

  // Initialize Firebase
  // const app = initializeApp(firebaseConfig);

   // Initialize Firebase
   firebase.initializeApp(firebaseConfig);
   firebase.analytics();

   var database = firebase.database();


//a mouse click into image, image change 
//lamp turn off or lamp turn on
// function changeColor()
// {
//     if( document.getElementById("image").src.endsWith("ledOff.png") )
//         document.getElementById("image").src = "./image/ledOn.png";
//     else
//         document.getElementById("image").src = "./image/ledOff.png";
// }

// press button change state lamp
// function OnIntoOff() {
//     document.getElementById("img-1").src = 
//     "./image/ledOff.png";
// }

// function OffIntoOn() {
//     document.getElementById("img-1").src = 
//     "./image/ledOn.png";
// }

// display variable
// function changeTemprature() {
//     var temp =800;
//     document.getElementById("nhietdo").innerHTML = temp;
// }
// changeTemprature();

//turn on or turn off lamp with temprature
// var tempratureChange=100;
// function imgChangeTemprature() {
//     var temp1 = 50;
//     if(temp1<100)
//         document.getElementById("img-1").src = 
//         "./image/ledOff.png";
//     else
//         document.getElementById("img-1").src = 
//         "./image/ledOn.png";
// }
// imgChangeTemprature();


var buttonOn = document.getElementById("button_1");
var buttonOff = document.getElementById("buttoff_1");

buttonOn.onclick = function() {
  // document.getElementById("img_1").src =  "./image/ledOn.png";
  database.ref("/control").update({
    "led": 1
  });

}

buttonOff.onclick = function() {
  // document.getElementById("img_1").src =  "./image/ledOff.png";
  database.ref("/control").update({
    "led": 0
  });

}

// get temp from 5base (auto update when data change)
database.ref("/Node1/co").on("value", function(snapshot){
  if(snapshot.exists())
  {
    var temp = snapshot.val();
    document.getElementById("nhietdo").innerHTML = temp;
  }
  else
    console.log("No data available");
  
});

// auto update img lamp
database.ref("/control/led").on("value", function(snapshot){
  var states = snapshot.val();

  console.log(states);
  if(states==1)
    document.getElementById("img_1").src =  "./image/ledOn.png";
  else
    document.getElementById("img_1").src =  "./image/ledOff.png";
});


