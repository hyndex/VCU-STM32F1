Generic Profiles Mapping

This codebase exposes generic, de-branded names in the parameter UI while retaining the underlying, proven drivers. The table below documents the mapping so existing setups remain understandable.

- VEHMODES
  - Vehicle_A → Cluster CAN profile (src/vehicles/cluster_can_vehicle.cpp with SetAlternateCluster(true))
  - Vehicle_B → Luxury CAN profile (src/vehicles/luxury_can_vehicle.cpp)
  - Vehicle_C → Cluster CAN profile (src/vehicles/cluster_can_vehicle.cpp with SetAlternateCluster(false))
  - Vehicle_D → Multi-platform CAN profile (src/vehicles/multi_can_vehicle.cpp)
  - Vehicle_E → AWD CAN profile (src/vehicles/awd_can_vehicle.cpp)
  - Vehicle_F → Analog CAN profile (src/vehicles/analog_can_vehicle.cpp)
  - Classic → Classic analog/IO profile (src/vehicles/classic_io_vehicle.cpp)
  - None → No vehicle integration

- SHIFTERS
  - Shifter_A → CAN shifter A (src/shifters/can_shifter_a.cpp)
  - Shifter_B → CAN shifter B (src/shifters/can_shifter_b.cpp)
  - Shifter_C → CAN shifter C (src/shifters/can_shifter_c.cpp)
  - Shifter_D → CAN shifter D (src/shifters/can_shifter_d.cpp)

- INVMODES
  - Inverter_A → Leaf_Gen1 (src/leafinv.cpp)
  - Inverter_B → GS450H (src/GS450H.cpp)
  - Inverter_C → Prius_Gen3 (src/GS450H.cpp with SetPrius())
  - Inverter_D → Outlander front (src/outlanderinverter.cpp)
  - Inverter_E → GS300H (src/GS450H.cpp with SetGS300H())
  - Inverter_F → RearOutlander (src/rearoutlanderinverter.cpp)
  - UserCAN → OpenInverter CAN (src/Can_OI.cpp)
  - OpenI → OpenInverter protocol (src/Can_OI.cpp)

- CHGMODS (On-board AC chargers)
  - External_Digital → extCharger (src/chargers/extCharger.cpp)
  - Charger_A → AC charger A (src/chargers/ac_charger_a.cpp)
  - Charger_B → AC charger B (src/chargers/ac_charger_b.cpp)
  - Charger_C → AC charger C (src/chargers/ac_charger_c.cpp)
  - Charger_D → AC charger D (src/chargers/ac_charger_d.cpp)
  - Charger_E → AC charger E (src/chargers/ac_charger_e.cpp)

- CHGINT (DC fast charge interfaces)
  - DCFC_A → i3 LIM CCS (src/i3LIM.cpp)
  - DCFC_B → CHAdeMO (src/chademo.cpp)
  - DCFC_C → CPC CCS (src/CPC.cpp)
  - DCFC_D → FOCCCI CCS (src/Foccci.cpp)

- HTTYPE (Cabin heaters)
  - Heater_A → CAN heater A (src/heaters/heater_can_a.cpp)
  - Heater_B → LIN heater A (src/heaters/heater_lin_a.cpp)
  - Heater_C → CAN heater B (src/heaters/heater_can_b.cpp)

- SHNTYPE (Current/voltage measurement)
  - Shunt_A → ISA shunt (src/isa_shunt.cpp)
  - Shunt_B → BMW SBOX (src/bmw_sbox.cpp)
  - Shunt_C → Multi-platform measurement box (src/multi_can_vehicle.cpp)

- PINFUNCS update
  - TransPump label replaces GS450pump. Functionality unchanged; see utils::GS450hOilPump.

Notes
- Labels and source modules now share the same generic naming.
- Existing configurations continue to work; only the display names differ.
