Import("env")
# so that our reserved region shows up properly in the size usage..
env.Replace(SIZEPROGREGEXP=r"^(?:\.text|\.isr_vector|\.reserved_flash|\.data|\.rodata|\.text.align|\.ARM.exidx)\s+(\d+).*")