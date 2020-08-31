# bs-firebase

## Setup

Install module
```bash
yarn add @dck/bs-firebase
```

Add it to `bsconfig.json`
```bash
{
  "bs-dependencies": [
    ...,
    "@dck/bs-firebase"
  ]
}
```

## Initialize app

```reason
open BsFirebase;

[@bs.module]
external firebaseConfig: firebaseConfig = "./config/firebase-config.json";

firebase->initializeApp(firebaseConfig);
```

## Authentication

First include the 'firebase/auth' module in our app bundle.

    BsFirebase.Auth.(require);

#### Watch for user change

```reason
firebase
->auth
->Auth.onAuthStateChanged(user => {
  switch (user->Js.Nullable.toOption) {
  | None => ()
  | Some(u) =>
    Js.log3(
      u->Auth.User.uid,
      u->Auth.User.email,
      u->Auth.User.displayName,
    )
  }
});

let signInWithGoogle = () => firebase->auth->Auth.signInWithPopup(Auth.Provider.google());
let signInWithEmailAndPassword = (~email, ~password) => firebase->auth->Auth.signInWithEmailAndPassword(~email, ~password);
let signOut = () => firebase->auth->Auth.signOut();
```

#### Sign in etc

```reason
Js.Promise.(
  BsFirebase.(firebase->auth->Auth.signInWithEmailAndPassword(~email, ~password))
  |> then_(value => {
       Js.log(value);
       Js.Promise.resolve(value);
    })
  |> ignore
);
```

#### Get token

```reason
Js.Promise.(
  firebase->auth->Auth.currentUser->Auth.User.getIdToken()
  |> then_(value => {
       Js.log(value);
       Js.Promise.resolve(value);
     })
  |> ignore
);
```

## Firestore

#### Fetch all

```reason
let fetchAll = () => {
  firebase
    ->firestore
    ->Firestore.collection("mycollection")
    ->Firestore.Collection.get()
    |> Js.Promise.then_(querySnapshot =>
        querySnapshot
        ->Firestore.QuerySnapshot.docs
        ->Belt.Array.map(snapshot => {
            let data = snapshot->Firestore.DocRef.data();
            Js.log(snapshot->Firestore.DocRef.id);
            Js.log(data##someAttribute);

            data;
          })
        |> Js.Promise.resolve
      );
};
```

#### Fetch by id

```reason
let fetchItem = (id) => {
  firebase
  ->firestore
  ->Firestore.collection("mycollection")
  ->Firestore.Collection.doc(id)
  ->Firestore.Collection.DocRef.get()
  |> Js.Promise.then_(doc => {
       let data = doc->Firestore.DocSnapshot.data();
       Js.log(data);

       data;
     });
}
```

#### Create

```reason
let create = (title, description) =>
  firebase
  ->firestore
  ->Firestore.collection("collection")
  ->Firestore.Collection.add({
    "title": title,
    "description": description,
  });
```

#### Update

```reason
let update = (id, title) =>
  firebase
  ->firestore
  ->Firestore.collection("collection")
  ->Firestore.Collection.doc(id)
  ->Firestore.Collection.DocRef.set(
      {"title": title},
      ~options=Firestore.Collection.DocRef.setOptions(~merge=true),
      (),
    );
```

#### Remove

```reason
let remove = (id: string) =>
  firebase
  ->firestore
  ->Firestore.collection("mycollection")
  ->Firestore.Collection.doc(id)
  ->Firestore.Collection.DocRef.delete();
```
