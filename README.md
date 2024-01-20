# Tools

## TODO

- Write README.md
- Add doxyfile
- Doxygen comments
- Clarify all options


## Tools configuration

### Set configuration

Default global configuration for tools is located in `tools_opt.h` header.

If you want to define your own configuration for tools, create config header, and set its name for define `TOOLS_OPT` in makefile or project config.
For ex, you created `-DTOOLS_OPT="my_tools_opt.h"`

### Options

`TOOLS_ALLOC_ENABLED`
`TOOLS_ASSERT_ENABLED`
`TOOLS_BUF_DEBUG_LEVEL`
`TOOLS_BUFFER_ENABLED`
`TOOLS_CLIOPT_ENABLED`
`TOOLS_COLOR_ENABLED`
`TOOLS_CRC_ENABLED`
`TOOLS_DEBUG_ENABLED`
`TOOLS_DEMUX_DEBUG_LEVEL`
`TOOLS_DEMUX_ENABLED`
`TOOLS_DLIST_ENABLED`
`TOOLS_DTC_ENABLE`
`TOOLS_FIFO_ENABLED`
`TOOLS_LOG_LEVEL`
`TOOLS_PRINT_ENABLED`
`TOOLS_PRINT_LEVEL`
`TOOLS_RANDOM_ENABLED`
`TOOLS_SLIST_ENABLED`
`TOOLS_STRING_ENABLED`
`TOOLS_THREAD_DBG_LEVEL`
`TOOLS_THREAD_ENABLED`
`TOOLS_TIME_ENABLED`
`TOOLS_TIMER_DBG_LEVEL`
`TOOLS_TIMER_ENABLED`
`TOOLS_TRACE_LOG_LEVEL`
`TOOLS_TRACE_PRINT_LEVEL`