import setuptools

module = setuptools.Extension(
    "cmod._cmod",
    sources=["cmod/_cmodule.cc"],
    language="c++"
)

if __name__ == "__main__":
    setuptools.setup(
        name="hello-c-extension",
        version="0.4",
        description="Showcase use and packaging of a C++ extension module",
        long_description=open("README.md").read(),
        long_description_content_type="text/markdown",
        url="https://github.com/bsolomon1124/hello-c-extension",
        author="Brad Solomon",
        author_email="bsolomon@protonmail.com",
        license="MIT",
        packages=["cmod"],
        ext_modules=[module],
        classifiers=[
            'Development Status :: 3 - Alpha',
            'Intended Audience :: Developers',
            'License :: OSI Approved :: MIT License',
            'Programming Language :: Python :: 3',
            'Programming Language :: Python :: 3.4',
            'Programming Language :: Python :: 3.5',
            'Programming Language :: Python :: 3.6',
            'Programming Language :: Python :: 3.7',
            'Programming Language :: Python :: 3.8',
            'Programming Language :: Python :: 3.9',
            'Programming Language :: Python :: 3 :: Only',
        ],
    )
