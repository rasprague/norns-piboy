
local models = {}

models['USB,2-axis 8-button gamepad  '] = require 'gamepad_model/ibufalo_classic_usb'
models['DWC OTG Controller'] = require 'gamepad_model/psx_usb_adapted'
models['8Bitdo NES30 Pro'] = require 'gamepad_model/8bitdones30pro'

return models
