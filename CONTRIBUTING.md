# Contributing to libui-node

✨ Thanks for contributing to libui-node! ✨

Please note that this project is released with a [Contributor Code of Conduct](CODE-OF-CONDUCT.md). By participating in this project you agree to abide by its terms.

## How can I contribute?

### Improve documentation

As a user of libui-node you're the perfect candidate to help us improve our documentation. Typo corrections, error fixes, better explanations, more examples, etc. Open issues for things that could be improved. [Documentation](https://github.com/parro-it/libui-napi/tree/master/docs), anything. Even improvements to this document.

Use the [`docs` label](https://github.com/parro-it/libui-node/labels/docs) to find suggestions for what we'd love to see more documentation on.

Many documents in `docs` folder are generated from JavaScript annotated source code contained in [js](https://github.com/parro-it/libui-napi/tree/master/js) folder.
If you want to improve that documents, you should change the anotains in source code,
and then recreate the markdown files by running `npm run docs`.

### Improve issues

Some issues are created with missing information, not reproducible, or plain invalid. Help make them easier to resolve. Handling issues takes a lot of time that we could rather spend on fixing bugs and adding features.

### Give feedback on issues

We're always looking for more opinions on discussions in the issue tracker. It's a good opportunity to influence the future direction of libui-node.

The [`question` label](https://github.com/parro-it/libui-node/labels/question) is a good place to find ongoing discussions.

### Write code

You can use issue labels to discover issues you could help out with:

* [`Waiting libui implementation` issues](https://github.com/parro-it/libui-node/labels/Waiting%20libui%20implementation) are issues blocked because we are waiting for libui to implements some features.
* [`Missing bind` issues](https://github.com/parro-it/libui-node/labels/Missing%20bind) are issues related to some piece of libui we haven't yet wrote bindings for.
* [`bug` issues](https://github.com/parro-it/libui-node/labels/bug) are known bugs we'd like to fix.
* [`loop` issues](https://github.com/parro-it/libui-node/labels/memory) are issues related to the event loop.
* [`memory` issues](https://github.com/parro-it/libui-node/labels/loop) are issues related to memory management.
The [`help wanted`](https://github.com/libui-nodejs/libui-node/labels/help%20wanted) and [`good for beginner`](https://github.com/libui-nodejs/libui-node/labels/good%20for%20beginner) labels are especially useful.

You may find an issue is assigned, or has the [`assigned` label](https://github.com/libui-nodejs/libui-node/labels/assigned). Please double-check before starting on this issue because somebody else is likely already working on it.

We'd like to fix [`priority` issues](https://github.com/libui-nodejs/libui-node/labels/priority) first. We'd love to see progress on [`low-priority` issues](https://github.com/libui-nodejs/libui-node/labels/low%20priority) too. [`future` issues](https://github.com/libui-nodejs/libui-node/labels/future) are those that we'd like to get to, but not anytime soon. Please check before working on these since we may not yet want to take on the burden of supporting those features.

If you're updating dependencies, please make sure you use npm@5.6.0 and commit the updated `package-lock.json` file.

### Versioning

We are not following semver, until libui-node reach 1.0.0.

Every time you are writing a new feature, please base your PR on the branch specific to the next release. E.g. if we just shipped version 0.13.0, you will find a branch 0_14_0 where
we are working on the new release. Do your work based on that branch in order to make the feature included in next release.

If you are solving a bug, you can work normally in master.

If you are writing a significant part of code, be sure to reach out to one of the maintainers in issues or in our [spectrum chat](https://spectrum.chat/libui-node) to discuss the implementation.

### Hang out in our chat

We have a [chat](https://spectrum.chat/libui-node). Jump in there and lurk, talk to us, and help others.

## Submitting an issue

- The issue tracker is for issues. Use our [chat](https://spectrum.chat/libui-node) or [Stack Overflow](https://stackoverflow.com/questions/tagged/libui-node) for support.
- Search the issue tracker before opening an issue.
- Ensure you're using the latest version of libui-node.
- Use a clear and descriptive title.
- Include as much information as possible: Steps to reproduce the issue, error message, Node.js version, operating system, etc.
- The more time you put into an issue, the more we will.
- [The best issue report is a failing test proving it.](https://twitter.com/sindresorhus/status/579306280495357953)

## Submitting a pull request

- Non-trivial changes are often best discussed in an issue first, to prevent you from doing unnecessary work.
- For ambitious tasks, you should try to get your work in front of the community for feedback as soon as possible. Open a pull request as soon as you have done the minimum needed to demonstrate your idea. At this early stage, don't worry about making things perfect, or 100% complete. Add a [WIP] prefix to the title, and describe what you still need to do. This lets reviewers know not to nit-pick small details or point out improvements you already know you need to make.
- New features should be accompanied with tests and documentation.
- Don't include unrelated changes.
- Lint and test before submitting the pull request by running `$ npm test`.
- Make the pull request from a [topic branch](https://github.com/dchelimsky/rspec/wiki/Topic-Branches), not master.
- Use a clear and descriptive title for the pull request and commits.
- Write a convincing description of why we should land your pull request. It's your job to convince us. Answer "why" it's needed and provide use-cases.
- You might be asked to do changes to your pull request. There's never a need to open another pull request. [Just update the existing one.](https://github.com/RichardLitt/knowledge/blob/master/github/amending-a-commit-guide.md)

*Looking to make your first ever contribution to an open-source project? Look no further! libui-node may be one of the most welcoming projects and communities out there. Check out ["Making your first contribution"](https://medium.com/@vadimdemedes/making-your-first-contribution-de6576ddb190) blog post to start off the right way and make your work a part of libui-node!*


# Other stuff

* Each `libui` control implementation is written in it's own C++ file in `src` folder.
* Each control is implemented in it's own C++ class, each class is a simple wrapper of related libui C functions.
* Header files are in `src/includes` folder.
* Control events does not follow `node` convention: if you attach an handler to an event, previous one will be overwritten and never be called.
* We build the project using the awesome [nbind](https://github.com/charto/nbind) tool, that automate the process of linking a straight C++ class to Node.js stuff...
