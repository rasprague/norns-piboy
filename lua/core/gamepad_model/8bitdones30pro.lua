
local g = {
  hid_name = '8Bitdo NES30 Pro',
  alias = '8Bitdo NES30 Pro',

  button = {
    A = 304+0,
    B = 304+1,
    X = 304+3,
    Y = 304+4,
    L1 = 304+6,
    R1 = 304+7,
    SELECT = 304+10,
    START = 304+11,
  },

  axis_invert = {
    Y = false,
    X = true,
  },

  dpad_is_analog = true,

  analog_axis_resolution = 256,
  -- margin to handle noise on center position
  analog_axis_o_margin = {
    X = 2,
    Y = 2,
  },
}

return g
