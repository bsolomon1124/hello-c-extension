from unittest import TestCase

from cmod import CONSTANT, pymod, _cmod


class TestExtension(TestCase):
    def test_1(self):
        self.assertEqual(CONSTANT, 10)

    def test_2(self):
        self.assertEqual(_cmod.foo(), 5)

    def test_3(self):
        self.assertIsNone(pymod.hello())
