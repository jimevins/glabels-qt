
Developers:
===========

The official glabels repository is located at

  https://github.com/jimevins/glabels-qt

The glabels coding style is documented in the file
[CODING-STYLE.md](CODING-STYLE.md) located in this directory.

See below for additional guidelines.


Translators:
============

TBD


ROADMAP
=======

TBD


BRANCHES
========

gLabels will typically have 2 active branches: a stable branch and a
development branch.


Stable branch
-------------

A stable branch will maintained in a git branch named glabels-major.minor.
E.g. "glabels-4.0".  Some characteristics of a stable branch:

- Prerequisites are fixed for the lifetime of the branch.
- The primary purpose of releases within a branch is to fix bugs.
- Besides bug fixes, releases may also include new and updated translations,
  updated documentation, and new label templates.
- Generally, no new features will be introduced by a release within a
  stable branch unless it is necessary to fix a bug.  Such a fix should not
  introduce new prerequisites.
- Nor will code be refactored unless it is necessary to fix a bug.


Unstable/development branch
---------------------------

The current development branch is maintained in the Git master branch.
Some characteristics of the development branch:

- Prerequisites are volatile and may change release to release.
- The primary purpose of releases is to introduce new features and
  get them in the hands of testers.
- Features and file formats may be volatile and change release to
  release.
- No attempt will be made to maintain backwards compatibility with
  development releases.


Version numbering
-----------------

* Versions are numbered major.minor.micro (e.g. 4.0.3)
* major version indicates a major change in architecture or technology
  - 2.x.x was based on gtk+-2
  - 3.x.x was based on gtk+-3
  - 4.x.x is based on qt-5
* minor version indicates a minor change in features or design
 - even minor versions are from a stable branch
 - odd minor versions are from a development branch
* micro version indicates a bugfix release
  - See above for release characteristics within a stable branch
 
