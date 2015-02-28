#define OFFS  "   |"
#define LOFFS "   \\"
#define EOFFS "    "

#define offsetcheck() 	if (last) { \
		offset.erase(offset.end()-4, offset.end()); \
		offset += EOFFS; \
	}
