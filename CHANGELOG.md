# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [0.6.0] - 2026-04-18

### Added

- `uv`-based development workflow (`uv sync`, `uv run`, `uv build`).
- `ruff` for linting and formatting; `ty` for type checking.
- `pytest` + `pytest-cov` with a 75% coverage floor (actual: 100%).
- Type stubs (`cmod/_cmod.pyi`) and PEP 561 `py.typed` marker shipped in
  the wheel.
- `CHANGELOG.md`, `CLAUDE.md`, and `.editorconfig`.
- `Taskfile.yml` with `task` shortcuts for sync/test/lint/format/build/hooks/clean/check.
- `.pre-commit-config.yaml` (runnable via `prek`) with ruff, ty,
  markdownlint-cli2, and basic hygiene hooks.
- `.github/dependabot.yml` covering the `uv` and `github-actions` ecosystems.
- GitHub Actions CI across Linux, macOS, and Windows for Python 3.10-3.14
  with lint, format, type, test, coverage, and build jobs.
- `.github/workflows/publish.yml`: tag-triggered publish using PyPI
  Trusted Publishing (OIDC), Sigstore signing, SBOM via `uv export`, and
  GitHub Release creation. All actions SHA-pinned.
- `uv.lock` committed for reproducible developer environments.
- Tests asserting correct module `__name__` and presence of docstrings.
- README shields.io badges for PyPI version, license, and Python versions.

### Changed

- Packaging: all metadata moved to `pyproject.toml` (PEP 621) with
  `setuptools` as the PEP 517 backend. C++ extension declared via
  `[[tool.setuptools.ext-modules]]`.
- `pyproject.toml`: PEP 639 SPDX license field (`license = "MIT"`,
  `license-files = ["LICENSE"]`); removed redundant license classifier.
- Ruff ruleset broadened (A, ARG, B, C4, ERA, FBT, ISC, N, PIE, PL, PT,
  PTH, RET, RUF, S, SIM, SLF, TC) while remaining targeted.
- Python support narrowed to `>=3.10, <3.15`.
- `cmod.__version__` and `cmod.CONSTANT` now use `Final` / `Literal` typing.
- Expanded test suite (stdout capture, version shape check).
- `Makefile` removed in favor of `Taskfile.yml`.
- README rewritten for the `task`-based workflow and release process.
- CLAUDE.md follows Anthropic's CLAUDE.md best-practice guidance.
- Tests converted to idiomatic pytest style (plain `assert`) from
  unittest-style methods.
- C++ extension migrated to **multi-phase initialization** (PEP 489): uses
  `PyModuleDef_Init` + `Py_mod_exec` slot instead of `PyModule_Create`.
- `PyModuleDef.m_size` set to `0` (stateless) instead of `-1`.
- Declares `Py_mod_multiple_interpreters` (3.12+) and `Py_mod_gil` (3.13+)
  slots for subinterpreter and free-threading compatibility.
- Function docstrings now defined via `PyDoc_STRVAR` for consistency.
- Removed unnecessary `(PyCFunction)` cast on `METH_NOARGS` function.

### Fixed

- `cmod._cmod.__name__` now correctly reports `"cmod._cmod"` instead of
  `"cmod"` (was caused by `PyModuleDef.m_name = "cmod"`). This affected
  pickling, logging, and module reprs.

### Removed

- `setup.py` (no longer needed with declarative extension modules).
- Python 2 compatibility branches in the C++ source.
- Author email address from package metadata.

## [0.5.0] - Prior

- Initial published version using legacy `setup.py` layout.
