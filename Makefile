build:
	python -m wheel version && python setup.py sdist bdist_wheel

clean:
	rm -rfv build dist *.egg-info
	python -m pip uninstall -qqq hello-c-extension

test:
	python -m unittest discover

locinstall:
	python -m pip install --force-reinstall -e .
