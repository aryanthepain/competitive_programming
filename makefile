clean: 
	rm -rf .cph/* *.bin *.exe
	rm -rf .cph
	@echo "compiled program files removed"
	@echo "cp helper files removed"

# to add to github repo
# make git m="message" b="your-branch(main by defualt)"
b?=main
m?=$(shell date '+%d-%m-%Y %H:%M:%S')
git:
	git add .
	git commit -m "$(m)"
	git push origin $(b)

push:
	git push origin $(b)

# Phony targets.
.PHONY: git push clean