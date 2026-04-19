# CLAUDE.md

## What this project is

Demo repo showing how to ship a Python distribution that contains **both** a
pure-Python submodule (`cmod.pymod`) and a compiled **C++ extension**
submodule (`cmod._cmod`) under one package. The C++ extension is the point —
don't treat it as incidental.

## Bash commands

- `task sync` — create `.venv` and install project + dev deps
- `task test` — pytest with coverage (fails under 75%)
- `task lint` — ruff check, ruff format check, ty check
- `task format` — auto-format + safe fixes
- `task build` — sdist + wheel into `dist/`
- `task hooks` — run all pre-commit hooks via `uvx prek run --all-files`
- `task check` — full verification pipeline

## Build backend (important)

Build backend is **`setuptools`**, not `uv_build`. `uv_build` is pure-Python
only and cannot compile C/C++ extensions. The extension is declared via
`[[tool.setuptools.ext-modules]]` in `pyproject.toml`. **Do not** migrate to
`uv_build` or reintroduce `setup.py`.

## Rebuilding the C extension

`uv sync` does **not** detect changes in `.cc` source. After editing
`src/cmod/_cmodule.cc`, run:

```bash
uv sync --reinstall-package hello-c-extension
```

## Code style rules that differ from defaults

- No `setup.py` / `setup.cfg` / `requirements.txt` — all metadata lives in
  `pyproject.toml` (PEP 621).
- Python target is `>=3.10, <3.15`. Do not use syntax that breaks 3.10.
- The C++ source is CPython-3-only; old `PY_MAJOR_VERSION < 3` branches
  were removed intentionally.
- **No author email** in package metadata. Do not reintroduce one.
- Multi-phase init (PEP 489) for the C extension — do not revert to
  `PyModule_Create`.

## Typing

- Prefer `Final` + `Literal` for constants (`CONSTANT: Final[Literal[10]]`).
- `Protocol`, `TypedDict`, and PEP 695 generics are currently not applicable
  — the API surface is one function and one constant. Do not introduce them
  artificially.

## Publishing

Tag-triggered via `.github/workflows/publish.yml`. Uses PyPI Trusted
Publishing (OIDC — no stored token), Sigstore signing, and an SBOM from
`uv export`. Requires a PyPI Trusted Publisher registration and a GitHub
environment named `pypi`.

## Common gotchas

- `m_name` in `PyModuleDef` must be the **fully qualified** dotted name
  (`"cmod._cmod"`), not just `"_cmod"` — otherwise `__name__`, pickling, and
  module reprs break.
- Designated-initializers for structs (`.m_base = ...`) require C++20; we
  use positional initialization for portability across compilers.

## Pull request titles

Follow Conventional Commits format: `<type>: <description>` (e.g. `chore: update dependencies`, `fix: handle edge case`, `feat: add new export`).
