build:
	python -m wheel version && python setup.py build bdist_wheel

clean:
	rm -rfv build dist *.egg-info

test:
	python -m unittest tests/*.py
