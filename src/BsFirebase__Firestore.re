type t;

module DocSnapshot = {
  type t;

  [@bs.get] external exists: t => bool = "exists";
  [@bs.get] external id: t => string = "id";
  [@bs.send] external data: (t, unit) => 'a = "data";
};

module QuerySnapshot = {
  type t;

  [@bs.get] external docs: t => array(DocSnapshot.t) = "docs";
  [@bs.get] external size: t => int = "size";
};

module Collection = {
  type t;

  module DocRef = {
    type t;

    [@bs.deriving abstract]
    type setOptions = {merge: bool};

    [@bs.send] external get: (t, unit) => Js.Promise.t(DocSnapshot.t) = "get";
    [@bs.send] external delete: (t, unit) => Js.Promise.t(unit) = "delete";
    [@bs.send]
    external set: (t, 'a, ~options: setOptions=?, unit) => Js.Promise.t(unit) =
      "set";
  };

  [@bs.send] external add: (t, 'a) => Js.Promise.t(DocRef.t) = "add";
  [@bs.send] external get: (t, unit) => Js.Promise.t(QuerySnapshot.t) = "get";
  [@bs.send] external doc: (t, string) => DocRef.t = "doc";
  [@bs.send]
  external where:
    (
      t,
      string,
      [@bs.string] [
        | [@bs.as "=="] `equal
        | [@bs.as ">"] `greater
        | [@bs.as ">="] `greaterEqual
        | [@bs.as "<"] `lower
        | [@bs.as "<="] `lowerEqual
        | [@bs.as "array-contains"] `arrayContains
      ],
      string
    ) =>
    t =
    "where";
};

[@bs.module] external require: t = "firebase/firestore";

[@bs.send] external collection: (t, string) => Collection.t = "collection";