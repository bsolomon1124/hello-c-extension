#!/usr/bin/env python

import re
import setuptools


def read_version():
    with open("src/cmod/__init__.py") as f:
        return re.search(
            r"""__version__\s+=\s+(['"])(?P<v>.+?)\1""",
            f.read()
        ).group('v')


if __name__ == "__main__":
    module = setuptools.Extension(
        "cmod._cmod",
        sources=["src/cmod/_cmodule.cc"],
        language="c++"
    )
    setuptools.setup(
        name="hello-c-extension",
        version=read_version(),
        description="Showcase use and packaging of a C++ extension module",
        long_description=open("README.md").read(),
        long_description_content_type="text/markdown",
        url="https://github.com/bsolomon1124/hello-c-extension",
        author="Brad Solomon",
        author_email="bsolomon@protonmail.com",
        license="MIT",
        packages=setuptools.find_packages("src"),
        package_dir={'': 'src'},
        ext_modules=[module],
        classifiers=[
            'Development Status :: 3 - Alpha',
            'Intended Audience :: Developers',
            'License :: OSI Approved :: MIT License',
            'Programming Language :: Python :: 3',
            'Programming Language :: Python :: 3.5',
            'Programming Language :: Python :: 3.6',
            'Programming Language :: Python :: 3.7',
            'Programming Language :: Python :: 3.8',
            'Programming Language :: Python :: 3.9',
            'Programming Language :: Python :: 3 :: Only',
        ],
        python_requires='>=2.7, !=3.0.*, !=3.1.*, !=3.2.*, !=3.3.*, !=3.4.*',
        zip_safe=False,
    )
