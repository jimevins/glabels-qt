How To Contribute to gLabels
============================

### Did you find a bug?

* **Ensure the bug has not already been reported** by searching on GitHub under [Issues](https://github.com/jimevins/glabels-qt/issues).  If you have additional information, please contribute to the discussion.

* If you are unable to find an open issue related to the problem, please [open a new one](https://github.com/jimevins/glabels-qt/issues/new).  Be sure to include a **title and clear description** of the problem, as much relevant information as possible, and if appropriate, any **example project files** that demonstrate the problem.


### Did you write a patch that fixes a bug?

* Open a new GitHub pull-request with the patch.

* Ensure the pull-request description clearly describes the problem and your solution.  Include the relevant issue number if applicable.

* Before submitting, please read [CODING-STYLE.md](CODING-STYLE.md).


### Do you intend to add a new feature or change an existing one?

* [Open an issue](https://github.com/jimevins/glabels-qt/issues/new) to discuss your plans and start writing code.

* Before submitting a pull-request, please read [CODING-STYLE.md](CODING-STYLE.md) located in this directory.


### Would you like to submit new product templates?

* Before submitting, please read [PRODUCT-TEMPLATES.md](PRODUCT-TEMPLATES.md) located in this directory.

* [Open an issue](https://github.com/jimevins/glabels-qt/issues/new) and attach your completed product template file(s).


### Would you like to provide translations?

* Guidelines TBD




gLabels Branching Model
-----------------------

At any time gLabels will typically have 2 active branches: a stable branch and a development branch (master).  Other branches may also exist to work on major features.


### Stable branch

A stable branch will maintained in a git branch named glabels-major.minor.
E.g. "glabels-4.0".  Some characteristics of a stable branch are

- Prerequisites are fixed for the lifetime of the branch.
- The primary purpose of releases within a branch is to fix bugs.
- Besides bug fixes, releases may also include new and updated translations,
  updated documentation, and new label templates.
- No new features will be introduced by a release within a
  stable branch.


### Unstable/development branch

The current development branch is maintained in the Git master branch.
Some characteristics of the development branch are

- Prerequisites are volatile and may change over time.
- Features and file formats may be volatile and change over time.
- No attempt will be made to maintain backwards compatibility between commits
- Every effort will be made to make sure the development branch will build and run without error.
- There will be no official unstable releases based on this branch.  However, CI snapshots may be made available.

### Major feature branches

Major features that could risk breaking the development branch will be developed in their own branches.


gLabels Version numbering
-------------------------

* Versions are numbered major.minor.micro (e.g. 4.0.3)
* major version indicates a major change in architecture or technology
  - 2.x.x was based on gtk+-2
  - 3.x.x was based on gtk+-3
  - 4.x.x is based on qt-5
* minor version indicates a minor change in features or design
  - A new stable branch will be created for each new minor version
* micro version indicates a bugfix release
  - See above for release characteristics within a stable branch
 
