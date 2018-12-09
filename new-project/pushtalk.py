import json
import logging
import os.path

import click
import grpc
import google.auth.transport.grpc
import google.auth.transport.requests
import google.auth.transport.credentials

from google.assistant.embeddedvlalphal import embedded_assistant_pb2

