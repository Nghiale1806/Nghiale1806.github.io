//...............................................................................

// TODO: Replace the following with your app's Firebase project configuration
// See: https://firebase.google.com/docs/web/learn-more#config-object
const firebaseConfig = {
   apiKey: "AIzaSyAbOjE9T1Y56v2hHz_FZOnSqF6SK1drd4o",
   authDomain: "tieuluantn.firebaseapp.com",
   databaseURL: "https://tieuluantn-default-rtdb.firebaseio.com",
   projectId: "tieuluantn",
   storageBucket: "tieuluantn.appspot.com",
   messagingSenderId: "1075602692575",
   appId: "1:1075602692575:web:63e4ffd13c092ce8660c6a",
};

// Initialize Firebase
firebase.initializeApp(firebaseConfig);

// Initialize Realtime Database and get a reference to the service
const database = firebase.database();

//................................................................................
var btnOn = document.getElementById("btnOnId_01");
var btnOff = document.getElementById("btnOffId_01");

//cap nhat so nguoi
database.ref("/Room1/Songuoi").on("value", function (snapshot) {
   var nguoi = snapshot.val();
   document.getElementById("songuoi").innerHTML = nguoi;
});
// cap nhat den
database.ref("/Room1/trangthaiden").on("value", function (snapshot) {
   var ss = snapshot.val();
   if (ss == 1)
      document.getElementById("den_01").innerHTML = "Đèn đang hoạt động";
   else document.getElementById("den_01").innerHTML = "Đèn đã tắt";

   const hinh_anh_den = document.getElementById("hinh_anh_den");

   if (ss == 1) {
      hinh_anh_den.src = "./den_on-transformed.png";
   } else {
      hinh_anh_den.src = "./den_off-transformed.png";
   }
});

 /*btnOn.onclick = function () {
    document.getElementById("den_01").src = "./den_on.png";
    database.ref("/Room1").update({
       Den: 1,
    });
 };
 btnOff.onclick = function () {
    document.getElementById("den_01").src = "./den_off.png";
    database.ref("/Room1").update({
       Den: 0,
    });
 };
// cap nhat so nguoi
// database.ref("/Room1/Songuoi").on("value", function (snapshot) {
//    var nguoi = snapshot.val();
//    document.getElementById("songuoi").innerHTML = nguoi;
// });
// cap nhat den
// database.ref("/Room1/trangthaiden").on("value", function (snapshot) {
//    var led = snapshot.val();
//    if (led == 1) document.getElementById("den_01").src = "./den_on.png";
//    else document.getElementById("den_01").src = "./den_off.png";
// });*/
