type firebase;
type firebaseConfig;

module Auth = BsFirebase__Auth;
module Firestore = BsFirebase__Firestore;

[@bs.module] external firebase: firebase = "firebase/app";

[@bs.send]
external initializeApp: (firebase, firebaseConfig) => unit = "initializeApp";

[@bs.send] external auth: firebase => Auth.t = "auth";
[@bs.send] external firestore: firebase => Firestore.t = "firestore";