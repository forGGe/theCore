#!/bin/python3

# Script validates JSON configuration, passed by user against provided schema.
# Subobject name is passed by the last argument.

import json
import sys
import os
from jsonschema import validate

cfg = json.load(open(sys.argv[1]))
schema = json.load(open(sys.argv[2]))

if len(sys.argv) > 3:
    cfg = cfg[sys.argv[3]]

validate(cfg, schema)
