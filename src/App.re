/* our dummy data */
let dummyRepo: RepoData.repo = {
  full_name: "jsdf/reason-react-hacker-news",
  stargazers_count: 27,
  html_url: "https://github.com/jsdf/reason-react-hacker-news",
};

let dummyRepos: array(RepoData.repo) = [|
  {
    stargazers_count: 27,
    full_name: "jsdf/reason-react-hacker-news",
    html_url: "https://github.com/jsdf/reason-react-hacker-news",
  },
  {
    stargazers_count: 93,
    full_name: "reasonml/reason-tools",
    html_url: "https://github.com/reasonml/reason-tools",
  },
|];
let optionalDummyRepo: option(RepoData.repo) = Some(dummyRepo);
// [@react.component]
// let make = () => {
//   // let (repoData, _setRepoData) = React.useState(() => optionalDummyRepo);
//   let (repoData, _setRepoData) = React.useState(() => Some(dummyRepo));
//   let repoItem =
//     switch (repoData) {
//     | Some(repo) => <RepoItem repo />
//     | None => ReasonReact.string("Loading")
//     };
//   <div> <h1> {ReasonReact.string("Reason Projects")} </h1> repoItem </div>;
// };
[@react.component]
let make = () => {
  // let (repoData, _setRepoData) = React.useState(() => optionalDummyRepo);
  let (repoData, setRepoData) = React.useState(() => None);

  let loadedReposButton =
    <button onClick={_event => setRepoData(_prev => Some(dummyRepos))}>
      {ReasonReact.string("Load Repos")}
    </button>;

  let repoItems =
    switch (repoData) {
    | Some(repos) =>
      ReasonReact.array(
        Array.map(
          (repo: RepoData.repo) => <RepoItem key={repo.full_name} repo />,
          repos,
        ),
      )
    | None => loadedReposButton
    };
  <div> <h1> {ReasonReact.string("Reason Projects")} </h1> repoItems </div>;
};