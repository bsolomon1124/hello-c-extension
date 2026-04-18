"""Tests for the :mod:`cmod` package."""

from __future__ import annotations

import io
from contextlib import redirect_stdout

from cmod import CONSTANT, __version__, _cmod, pymod


def test_constant() -> None:
    assert CONSTANT == 10


def test_version_is_semver() -> None:
    parts = __version__.split(".")
    assert len(parts) == 3
    for part in parts:
        assert part.isdigit()


def test_c_extension_foo() -> None:
    assert _cmod.foo() == 5


def test_c_extension_module_name() -> None:
    """Fully-qualified __name__ matters for pickling, logging, reprs."""
    assert _cmod.__name__ == "cmod._cmod"


def test_c_extension_has_docstrings() -> None:
    assert _cmod.__doc__ is not None
    assert _cmod.foo.__doc__ is not None


def test_pymod_hello_returns_none() -> None:
    assert pymod.hello() is None


def test_pymod_hello_prints() -> None:
    buf = io.StringIO()
    with redirect_stdout(buf):
        pymod.hello()
    assert buf.getvalue().strip() == "Hello from Python!"
