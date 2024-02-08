"""CSC148 Assignment 0

CSC148 Winter 2024
Department of Computer Science,
University of Toronto

This code is provided solely for the personal and private use of
students taking the CSC148 course at the University of Toronto.
Copying for purposes other than this use is expressly prohibited.
All forms of distribution of this code, whether as given or with
any changes, are expressly prohibited.

Author: Jonathan Calver and Sophia Huynh

All of the files in this directory are
Copyright (c) Jonathan Calver, Diane Horton, and Sophia Huynh.

Module Description:

Run this file to see the code coverage report for Task 5.

You will not hand this file in when submitting the assignment.
"""

if __name__ == '__main__':
    import coverage
    import pytest
    from python_ta import contracts

    # Note: If you are finding that the code coverage is running slowly,
    # you can uncomment out the line below, which disables pyTA's
    # check_contracts feature while running the coverage checks.
    # contracts.ENABLE_CONTRACT_CHECKING = False

    # This is the basic usage of coverage; include lists which files we
    # want the coverage report for.
    cov = coverage.Coverage(include=['four_in_a_row.py'])
    cov.start()

    # call your code for coverage
    pytest.main(["test_a0.py"])

    cov.stop()
    cov.save()

    # generate the html report (similar to what pyTA does)
    # and print the coverage percentage
    percent_covered = cov.html_report()

    print(f'Code coverage: {percent_covered :.2f}%')

    # code below will open up the detailed report in the browser (like pyTA).
    import webbrowser
    import os.path

    webbrowser.open(f'file://{os.path.dirname(__file__)}/htmlcov/index.html')
