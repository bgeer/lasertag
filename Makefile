.PHONY: clean All

All:
	@echo "----------Building project:[ 07-02-compressor-decompressor -  ]----------"
	@cd "07-02-compressor-decompressor" && "$(MAKE)" -f  "07-02-compressor-decompressor.mk"
clean:
	@echo "----------Cleaning project:[ 07-02-compressor-decompressor -  ]----------"
	@cd "07-02-compressor-decompressor" && "$(MAKE)" -f  "07-02-compressor-decompressor.mk" clean
