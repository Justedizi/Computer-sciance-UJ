SHELL := /bin/sh

test:
	perl -f check.pl; \
	perl -f run_tests.pl

submit:
	baca submit --no-main --no-save --task-id $$(cat .taskid) --file $$(cat .file) --rename source.cpp;

refresh:
	baca refresh
