# hello-c-extension

[![PyPI version](https://img.shields.io/pypi/v/hello-c-extension.svg)](https://pypi.org/project/hello-c-extension/)
[![License: MIT](https://img.shields.io/pypi/l/hello-c-extension.svg)](https://github.com/bsolomon1124/hello-c-extension/blob/master/LICENSE)
[![Python versions](https://img.shields.io/pypi/pyversions/hello-c-extension.svg)](https://pypi.org/project/hello-c-extension/)

A minimal, working example of how to **package a Python project that combines
pure-Python code with a C++ extension module** — using modern
(PEP 517 / 621 / 639) `pyproject.toml`-based build configuration and the
[`uv`](https://docs.astral.sh/uv/) +
[`task`](https://taskfile.dev/) workflow.

The package `cmod` exposes:

| Name            | Kind                              | Defined in              |
| --------------- | --------------------------------- | ----------------------- |
| `cmod.CONSTANT` | package-level Python constant     | `src/cmod/__init__.py`  |
| `cmod.pymod`    | pure-Python submodule             | `src/cmod/pymod.py`     |
| `cmod._cmod`    | compiled C++ extension submodule  | `src/cmod/_cmodule.cc`  |

## Install

```bash
python -m pip install hello-c-extension
```

## Use

```python
>>> from cmod import CONSTANT, pymod, _cmod
>>> CONSTANT
10
>>> pymod.hello()
Hello from Python!
>>> _cmod.foo()
5
```

## Project layout

```text
hello-c-extension/
├── pyproject.toml            # PEP 621 metadata + ext-modules + tool config
├── uv.lock                   # reproducible dependency lock (committed)
├── Taskfile.yml              # command shortcuts (task ...)
├── .pre-commit-config.yaml   # hooks runnable via prek
├── CHANGELOG.md              # Keep a Changelog
├── CLAUDE.md                 # guidance for AI-assisted development
├── .editorconfig
├── .github/
│   ├── dependabot.yml        # weekly uv + github-actions updates
│   └── workflows/
│       ├── ci.yml            # lint + matrix test + build
│       └── publish.yml       # tag-triggered OIDC publish + Sigstore + release
├── src/cmod/
│   ├── __init__.py
│   ├── pymod.py              # pure-Python submodule
│   ├── _cmodule.cc           # C++ source for the compiled submodule
│   ├── _cmod.pyi             # type stubs for the compiled submodule
│   └── py.typed              # PEP 561 marker (shipped in wheel)
└── tests/
    └── test_cext.py          # pytest (unittest-style)
```

## Development

Requires Python 3.10 - 3.14, [`uv`](https://docs.astral.sh/uv/),
[`task`](https://taskfile.dev/), and a C++-capable compiler.

```bash
task sync       # create .venv and install project + dev deps
task test       # pytest + coverage (>=75% enforced)
task lint       # ruff check + ruff format --check + ty check
task format     # auto-format and apply safe fixes
task build      # uv build -> sdist + wheel into dist/
task hooks      # run all pre-commit hooks via `uvx prek run --all-files`
task check      # full verification: lint + tests + build
```

## Pre-commit hooks

Run via [`prek`](https://github.com/j178/prek) (drop-in
`pre-commit` replacement; shares `.pre-commit-config.yaml`):

```bash
uvx prek install      # install git hook
uvx prek run --all-files
```

Configured hooks: `ruff`, `ruff-format`, `ty`, `markdownlint-cli2`, and basic
hygiene (end-of-file fixer, trailing whitespace, check-ast, check-merge-conflict,
debug-statements, mixed-line-ending).

## Build backend

This project uses `setuptools` as the PEP 517 build backend. Astral's
`uv_build` backend is pure-Python only and cannot compile C/C++ extensions,
so `setuptools` with declarative `[[tool.setuptools.ext-modules]]` is used
instead. `uv` still drives the developer workflow (env, deps, build, run).

## Releasing

Releases are tag-driven. Pushing a `v*` tag triggers `publish.yml`:

1. Build sdist + wheel with `uv build`.
2. Export an SBOM (locked requirements) via `uv export`.
3. Publish to PyPI using
   [Trusted Publishing (OIDC)](https://docs.pypi.org/trusted-publishers/)
   — no API token stored in the repo.
4. Sign the distributions with [Sigstore](https://www.sigstore.dev/).
5. Create a GitHub Release containing the signed distributions and SBOM.

All GitHub Actions are pinned to full commit SHAs. Jobs run with
least-privilege `permissions:` scopes. The `pypi` GitHub environment can be
configured with protection rules (required reviewers, wait timers) for an
extra manual gate on releases.

## License

MIT - see [LICENSE](LICENSE).
