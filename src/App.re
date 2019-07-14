/* our dummy data */
let dummyRepo: RepoData.repo = {
  full_name: "jsdf/reason-react-hacker-news",
  stargazers_count: 27,
  html_url: "https://github.com/jsdf/reason-react-hacker-news",
};

// let dummyRepos: array(RepoData.repo) = [|
//   {
//     stargazers_count: 27,
//     full_name: "jsdf/reason-react-hacker-news",
//     html_url: "https://github.com/jsdf/reason-react-hacker-news",
//   },
//   {
//     stargazers_count: 93,
//     full_name: "reasonml/reason-tools",
//     html_url: "https://github.com/reasonml/reason-tools",
//   },
// |];
// dummyRepos parsed with bs-json
let dummyRepos: array(RepoData.repo) = [|
  RepoData.parseRepoJson(
    Js.Json.parseExn(
      {js|
        {
          "stargazers_count": 93,
          "full_name": "reasonml/reason-tools",
          "html_url": "https://github.com/reasonml/reason-tools"
        }
      |js},
    ),
  ),
|];

[@react.component]
let make = () => {
  let (repoData, setRepoData) = React.useState(() => None);

  let loadedReposButton =
    <button onClick={_event => setRepoData(_prev => Some(dummyRepos))}>
      {ReasonReact.string("Load Repos")}
    </button>;
  // Note that we're using the React.useEffect0 version of the function because we are passing None instead of a depency array as the second argument. There are additional versions which take dependency arrays as the second argument for different numbers of dependencies (useEffect1, useEffect2, etc.) which you can use as needed, but useEffect0 just takes None instead of an array.
  React.useEffect0(() => {
    RepoData.fetchRepos()
    |> Js.Promise.then_(repoData => {
         setRepoData(_prev => Some(repoData));
         Js.Promise.resolve();
       })
    |> Js.Promise.catch(err => {
         Js.log("An error occurred: " ++ Js.String.make(err));
         Js.Promise.resolve();
       })
    |> ignore;
    None; // so the effect will only run once, on mount. Also, the second arg to useEffect is the initial state so we are passing None option as initial state.
  });
  let repoItems =
    switch (repoData) {
    | Some(repos) =>
      ReasonReact.array(
        Array.map(
          (repo: RepoData.repo) => <RepoItem key={repo.full_name} repo />,
          repos,
        ),
      )
    | None => React.string("Loading...")
    };
  <div>
    <h1> {ReasonReact.string("Reason Projects")} </h1>
    <Timer />
    repoItems
  </div>;
};