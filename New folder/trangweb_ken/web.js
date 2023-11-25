//...............................................................................

// TODO: Replace the following with your app's Firebase project configuration
// See: https://firebase.google.com/docs/web/learn-more#config-object
// Import the functions you need from the SDKs you need
import { initializeApp } from "https://www.gstatic.com/firebasejs/9.9.0/firebase-app.js";
import { getDatabase, ref, set, child, get } from "https://www.gstatic.com/firebasejs/9.9.0/firebase-database.js";
import { getAnalytics } from "https://www.gstatic.com/firebasejs/9.9.0/firebase-analytics.js";
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
const app = initializeApp(firebaseConfig);
const analytics = getAnalytics(app);
//................................................................................
const dbRef = ref(getDatabase());
get(child(dbRef, `Room1` + '/Songuoi')).then((snapshot) => {
   var nguoi = snapshot.val();
   document.getElementById("songuoi").innerHTML = nguoi;
});
const dbRef_1 = ref(getDatabase());
get(child(dbRef_1, `Room1` + '/trangthaiden')).then((snapshot_1) => {
   var ss = snapshot_1.val();
   
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



var den_on_1 = document.getElementById("fanon_1");
var den_off_1 = document.getElementById("fanoff_1");
den_on_1.onclick = function(){
   const db = getDatabase();
   set(ref(db, 'Room1/trangthaiden/'), {
     Value : 1
    
   });
   
  }
  den_off_1.onclick = function(){
   const db = getDatabase();
   set(ref(db, 'Room1/trangthaiden/'), {
     Value : 0
    
   });

  }
   const dbRef = ref(getDatabase());
  get(child(dbRef, `Room1` + '/trangthaiden')).then((snapshot) => {
     var temp = snapshot.val();
     document.getElementById("doC_1").innerHTML = temp;
  });
  const dbRef_1 = ref(getDatabase());
  get(child(dbRef_1, `Room1` + '/trangthaiden')).then((snapshot_1) => {
     var temp_1 = snapshot_1.val();
     document.getElementById("doF_1").innerHTML = temp_1;
  });

  

// btnOn.onclick = function () {
//    document.getElementById("den_01").src = "./den_on.png";
//    database.ref("/Room1").update({
//       Led: 1,
//    });
// };
// btnOff.onclick = function () {
//    document.getElementById("den_01").src = "./den_off.png";
//    database.ref("/Room1").update({
//       Led: 0,
//    });
// };
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
// });
