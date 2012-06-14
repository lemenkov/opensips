# $Id$
#
# WARNING: do not run this directly, it should be run by the master Makefile

include ../../Makefile.defs
auto_gen=
NAME=db_oracle.so

DEFS +=-I$(ORAHOME)/include
LIBS +=-L$(ORAHOME)/lib -locci -lclntsh

include ../../Makefile.modules

.PHONY: $(UTILS_DIR)/db_oracle/opensips_orasel
$(UTILS_DIR)/db_oracle/opensips_orasel:
	make -C $(UTILS_DIR)/db_oracle

install_module_custom: $(bin_prefix)/$(bin_dir) $(UTILS_DIR)/db_oracle/opensips_orasel
	mkdir -p $(modules_prefix)/$(lib_dir)/opensipsctl ; \
	sed -e "s#/usr/local/sbin#$(bin-target)#g" \
		< $(SCRIPTS_DIR)/opensipsctl.oracle > /tmp/opensipsctl.oracle ; \
	$(INSTALL_CFG) /tmp/opensipsctl.oracle \
		$(modules_prefix)/$(lib_dir)/opensipsctl/opensipsctl.oracle ; \
	rm -fr /tmp/opensipsctl.oracle ; \
	sed -e "s#/usr/local/share/opensips#$(data_target)#g" \
	< $(SCRIPTS_DIR)/opensipsdbctl.oracle > /tmp/opensipsdbctl.oracle ; \
	$(INSTALL_TOUCH) $(modules_prefix)/$(lib_dir)/opensipsctl/opensipsdbctl.oracle ; \
	$(INSTALL_CFG) /tmp/opensipsdbctl.oracle $(modules_prefix)/$(lib_dir)/opensipsctl/ ; \
	rm -fr /tmp/opensipsdbctl.oracle ; \
	sed -e "s#/usr/local/share/opensips#$(data_target)#g" \
	< $(SCRIPTS_DIR)/opensipsdbfunc.oracle > /tmp/opensipsdbfunc.oracle ; \
	$(INSTALL_TOUCH) $(modules_prefix)/$(lib_dir)/opensipsctl/opensipsdbfunc.oracle ; \
	$(INSTALL_CFG) /tmp/opensipsdbfunc.oracle $(modules_prefix)/$(lib_dir)/opensipsctl/ ; \
	rm -fr /tmp/opensipsdbfunc.oracle ; \
	mkdir -p $(data_prefix)/$(data_dir)/oracle ; \
	for FILE in $(wildcard $(SCRIPTS_DIR)/oracle/*) ; do \
		if [ -f $$FILE ] ; then \
		$(INSTALL_TOUCH) $$FILE \
			$(data_prefix)/$(data_dir)/oracle/`basename "$$FILE"` ; \
		$(INSTALL_CFG) $$FILE \
			$(data_prefix)/$(data_dir)/oracle/`basename "$$FILE"` ; \
		fi ;\
	done ; \
	mkdir -p $(data_prefix)/$(data_dir)/oracle/inc ; \
	for FILE in $(wildcard $(SCRIPTS_DIR)/oracle/inc/*) ; do \
		if [ -f $$FILE ] ; then \
		$(INSTALL_TOUCH) $$FILE \
			$(data_prefix)/$(data_dir)/oracle/inc/`basename "$$FILE"` ; \
		$(INSTALL_CFG) $$FILE \
			$(data_prefix)/$(data_dir)/oracle/inc/`basename "$$FILE"` ; \
		fi ;\
	done ; \
	mkdir -p $(data_prefix)/$(data_dir)/oracle/admin ; \
	for FILE in $(wildcard $(SCRIPTS_DIR)/oracle/admin/*) ; do \
		if [ -f $$FILE ] ; then \
		$(INSTALL_TOUCH) $$FILE \
			$(data_prefix)/$(data_dir)/oracle/admin/`basename "$$FILE"` ; \
		$(INSTALL_CFG) $$FILE \
			$(data_prefix)/$(data_dir)/oracle/admin/`basename "$$FILE"` ; \
		fi ;\
	done ; \
	$(INSTALL_BIN) $(UTILS_DIR)/db_oracle/opensips_orasel $(bin_prefix)/$(bin_dir) ; \
