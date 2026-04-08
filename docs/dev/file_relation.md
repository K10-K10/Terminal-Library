# Module Structure

`screen  ←  renderer  ←  app`

## app
dependencies:
- renderer
- screen

role:
- orchestration

## renderer
dependencies:
- screen

role:
- rendering

## screen
dependencies:
- none

role:
- buffer
