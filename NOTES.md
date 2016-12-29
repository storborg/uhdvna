# Parts

2x TwinRX boards, A and B
4x Directional couplers, A, B, C, and D
1x External wideband amplifier, output return loss is important
1x Reference load
1x MMCX to SMA cable
2x MMCX to MMCX cable
7x SMA to SMA cable, short (ideally semirigid)
2x SMA to SMA cable, medium (phase stable, for test ports)

# Connections

DBoard A J1 (LO2 Export) - disconnected
DBoard A J2 (LO2 Input) - DBoard B J1 (LO2 Export)
DBoard B J2 (LO2 Input) - disconnected

DBoard A J3 (LO1 Export) - connected to external source amp input
DBoard A J4 (LO1 Input) - DBoard B J3 (LO1 Export)
DBoard B J4 (LO1 Input) - disconnected

External source amp input - Coupler A in
Coupler A out - Coupler B out
Coupler A coupled - DBoard A RX1
Coupler B in - Test port 1
Coupler B coupled - DBoard A RX2

Test port 2 - Coupler C in
Coupler C coupled - DBoard B RX2
Coupler C out - Coupler D out
Coupler D coupled - DBoard B RX1
Coupler D in - Reference load

# Strategy

Initialization:

- Set clock source to internal

- Set time source to internal

- Set LOs such that a single LO is exported externally, and one shared between boards
    - Set Board A CH1 LO1 export to yes
    - Set Board A CH1 LO2 export to no

    - Set Board A CH2 LO1 export to no
    - Set Board A CH2 LO2 export to no

    - Set Board B CH1 LO1 export to yes
    - Set Board B CH1 LO2 export to yes

    - Set Board B CH2 LO1 export to no
    - Set Board B CH2 LO2 export to no

- Set all other LO sources (for both boards) to share a single source
    - Set Board A CH1 LO1 source to companion
    - Set Board A CH1 LO2 source to companion

    - Set Board A CH2 LO1 source to external
    - Set Board A CH2 LO2 source to external

    - Set Board B CH1 LO1 source to companion
    - Set Board B CH1 LO2 source to companion

    - Set Board B CH2 LO1 source to internal
    - Set Board B CH2 LO2 source to internal

- Configure antenna sources
    - Set Board A CH1 source to RX1
    - Set Board A CH2 source to RX2
    - Set Board B CH1 source to RX1
    - Set Board B CH2 source to RX2

- Set gain of all channels (fixed value)

- Set sample rate of all channels (fixed value, 2MSPS?)

- Set rx bandwidth

To sample a point:

- Tune to test frequency minus IF with normal automatic tuning
    - Tune Board A CH1 to freq - ifbw
    - Tune Board A CH2 to freq - ifbw
    - Tune Board B CH1 to freq - ifbw
    - Tune Board B CH2 to freq - ifbw

- Tune exported LO to test frequency
    - Tune Board A CH1 LO1 to freq

- Wait for all LOs to lock

- Record waveform with duration that is IFBW coefficient * IFBW
    - Used timed start command for all channels to ensure coherency

- Bandpass filter

- Do final IF mixing

- Return I/Q
