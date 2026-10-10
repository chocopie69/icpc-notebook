"""Tests for the page-header renderer; run with Python 3."""
import importlib.util
import io
from pathlib import Path
import unittest

path = Path(__file__).resolve().parents[2] / "content/tex/preprocessor.py"
spec = importlib.util.spec_from_file_location("preprocessor", path)
preprocessor = importlib.util.module_from_spec(spec)
spec.loader.exec_module(preprocessor)


def render(entries):
    out = io.StringIO()
    preprocessor.print_header(entries, out)
    return out.getvalue()


class PageHeaders(unittest.TestCase):
    def test_blank_page(self):
        self.assertEqual(render(" | "), "")

    def test_duplicates_preserve_order(self):
        header = render("BigInt.h|BigInt.h|ModLog.h|BigInt.h")
        self.assertIn(r"BigInt\enspace{}ModLog", header)
        self.assertEqual(header.count("BigInt"), 1)

    def test_continuation_and_repeated_render(self):
        self.assertIn("BigInt", render("Polynomial.h|BigInt.h"))
        self.assertIn("BigInt", render("BigInt.h|ModLog.h"))
        self.assertEqual(render("BigInt.h"), render("BigInt.h"))

    def test_escape_and_small_font(self):
        self.assertIn(r"some\_algorithm", render("some_algorithm.h"))
        self.assertIn(r"\fontsize{8}{8}", render("x" * 151 + ".h"))


if __name__ == "__main__":
    unittest.main()
