"""Hybrid Python + C++ package.

Top-level package re-exporting a pure-Python submodule (:mod:`cmod.pymod`)
and a compiled C++ extension submodule (:mod:`cmod._cmod`).
"""

from typing import Final, Literal

from cmod import _cmod, pymod

__version__: Final[str] = "0.6.0"

CONSTANT: Final[Literal[10]] = 10

__all__ = ["CONSTANT", "__version__", "_cmod", "pymod"]
