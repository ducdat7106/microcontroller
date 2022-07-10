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

   var mydatabase = firebase.database();

   var Co_value = 0;
   var Gas_value = 0;
   var Dust_value = 0;
   var Sound_value = 0;

   var Co_set = 0;
   var Gas_set = 0;
   var Dust_set = 0;
   var Sound_set = 0;

   var safe_state = 'AN TOÀN';
   var danger_state = 'NGUY HIỂM';

// get temp from 5base (auto update when data change)
mydatabase.ref("/Node1/co").on("value", function(snapshot){
  if(snapshot.exists())
  {
    Co_value = snapshot.val();
    document.getElementById("co").innerHTML = Co_value;
  }
  else
    console.log("No data available");
});

mydatabase.ref("/Node1Set/co").on("value", function(snapshot){
  if(snapshot.exists())
  {
    Co_set = snapshot.val();
    if(Co_value>=Co_set)
    {
      document.getElementById("imgCo").src = "image/danger.png";
    }
    else
    {
      document.getElementById("imgCo").src = "image/safe.png";
    }  
  }
  else
    console.log("No data available");
});

mydatabase.ref("/Node1/gas").on("value", function(snapshot){
  if(snapshot.exists())
  {
    Gas_value = snapshot.val();
    document.getElementById("gas").innerHTML = Gas_value;
  }
  else
    console.log("No data available");
});

mydatabase.ref("/Node1Set/gas").on("value", function(snapshot){
  if(snapshot.exists())
  {
    Gas_set = snapshot.val();
    if(Gas_value>=Gas_set)
    {
      document.getElementById("imgGas").src = "image/danger.png";
    }
    else
    {
      document.getElementById("imgGas").src = "image/safe.png";
    }  
  }
  else
    console.log("No data available");
});


mydatabase.ref("/Node1/dust").on("value", function(snapshot){
  if(snapshot.exists())
  {
    Dust_value = snapshot.val();
    document.getElementById("dust").innerHTML = Dust_value;
  }
  else
    console.log("No data available");
});

mydatabase.ref("/Node1Set/dust").on("value", function(snapshot){
  if(snapshot.exists())
  {
    Dust_set = snapshot.val();
    if(Dust_value>=Dust_set)
    {
      document.getElementById("imgDust").src = "./image/danger.png";
    }
    else
    {
      document.getElementById("imgDust").src = "./image/safe.png";
    }
  }
  else
    console.log("No data available");
});


mydatabase.ref("/Node1/sound").on("value", function(snapshot){
  if(snapshot.exists())
  {
    Sound_value = snapshot.val();
    document.getElementById("sound").innerHTML = Sound_value;
  }
  else
    console.log("No data available");
});

mydatabase.ref("/Node1Set/sound").on("value", function(snapshot){
  if(snapshot.exists())
  {
    Sound_set = snapshot.val();
    if(Sound_value>=Sound_set)
    {
      document.getElementById("imgSound").src = "./image/danger.png";
    }
    else
    {
      document.getElementById("imgSound").src = "./image/safe.png";
    }
  }
  else
    console.log("No data available");
});


// lam tuoi trang web
let counter = 0;
setInterval(() => {
    if(Sound_value<Sound_set && Dust_value<Dust_set && Gas_value<Gas_set && Co_value<Co_set)
    {
      document.getElementById("result").innerHTML = 'AN TOÀN';
    }
    else  
    {
      document.getElementById("result").innerHTML = 'NGUY HIỂM';
    }

    // if(Sound_value>=Sound_set || Dust_value>=Dust_set || Gas_value>=Gas_set || Co_value>=Co_set)
    // {
    //   document.getElementById("result").innerHTML = 'NGUY HIỂM';
    // }
    // else
    // {
    //   document.getElementById("result").innerHTML = 'AN TOÀN';
    // }

    //document.querySelector('h2').innerText = counter;
    counter++;
    console.log(counter); 
    if(counter > 5) 
      location.reload();
}, 1000);

