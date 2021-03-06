## whenBlock

The `whenBlock` tool answers one of two questions: (1) "At what date and time did a given block occur?" or (2) "What block occurred at or before a given date and time?"

In the first case, one simply supplies a block number and the date and time of that block is displayed. In the later case, one provides a date (and optionally a time) and the block number that occurred at or just prior to that date and time is displayed.

The values for `date` and `time` are specified in JSON format. The `hour`/`minute`/`second` portions of the date are optional, and if omitted, default to zero in each case. Block numbers may be specified as either integers or hexidecimal values. You may specify any number of dates or blocks per invocation.

You may name your own blocks (for example, to denote the start of an ICO perhaps) by editing '~/.quickBlocks/quickBlocks.toml' and placing `name=blockNum` pairs under the `[special]` section of that file (create the file if it is not already present). Special blocks are detailed below.

#### Usage

`Usage:`    whenBlock [-l|-t|-s|-v|-h] &lt; block | date &gt; [ block... | date... ]  
`Purpose:`  Finds the nearest block prior to a date, or the nearest date prior to a block.
            Alternatively, search for one of 'special' blocks.

`Where:`  

| Short Cut | Option | Description |
| -------: | :------- | :------- |
|  | block_list | one or more dates, block numbers, hashes, or special named blocks (see notes) |
| -l | --list | export a list of the 'special' blocks |
| -t | --timestamps | ignore other options and generate timestamps only |
| -s | --skip <num> | only applicable if --timestamps is on, the step between block numbers in the export |
| -v | --verbose | set verbose level. Either -v, --verbose or -v:n where 'n' is level |
| -h | --help | display this help screen |

`Notes:`

- The block list may contain any combination of `number`, `hash`, `date`, special `named` blocks.
- Dates must be formatted in JSON format: YYYY-MM-DD[THH[:MM[:SS]]].
- You may customize the list of named blocks by editing ~/.quickBlocks/whenBlock.toml.
- The following `named` blocks are currently configured:
  - first (`0`), firstTrans (`46147`), firstContract (`50111`), iceage (`200000`)
  - devcon1 (`543626`), homestead (`1150000`), daofund (`1428756`), daohack (`1718497`)
  - daofork (`1920000`), devcon2 (`2286910`), tangerine (`2463000`), spurious (`2675000`)
  - stateclear (`2717576`), eea (`3265360`), ens2 (`3327417`), parityhack1 (`4041179`)
  - byzantium (`4370000`), devcon3 (`4469339`), parityhack2 (`4501969`), kitties (`4605167`)
  - makerdao (`4620855`), devcon4 (`6610517`), uniswap (`6627917`), constantinople (`7280000`)
  - devcon5 (`8700401`), mcdai (`8928158`), istanbul (`9069000`), muirglacier (`9200000`)
  - latest (``)

#### Other Options

All **TrueBlocks** command-line tools support the following commands (although in some case, they have no meaning):

    Command     |     Description
    -----------------------------------------------------------------------------
    --version   |   display the current version of the tool
    --nocolor   |   turn off colored display
    --wei       |   specify value in wei (the default)
    --ether     |   specify value in ether
    --dollars   |   specify value in US dollars
    --raw       |   report JSON data from the node with minimal processing
    --very_raw  |   report JSON data from node with zero processing
    --fmt       |   export format (where appropriate). One of [none|txt|csv|json|api]
    --to_file   |   write the results to a temporary file and return the filename
    --output:fn |   write the results to file 'fn' and return the filename
    --file:fn   |   specify multiple sets of command line options in a file.

<small>*For the `--file:fn` option, place a series of valid command lines in a file and use the above options. In some cases, this option may significantly improve performance. A semi-colon at the start of a line makes that line a comment.*</small>

**Powered by TrueBlocks<sup>&trade;</sup>**


