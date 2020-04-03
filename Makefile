build:
	python -m wheel version && python setup.py build bdist_wheel

clean:
	rm -rfv build dist *.egg-infop

test:
	python -m unittest tests/*.py
