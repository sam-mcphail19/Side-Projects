from flask import Flask
from flask_googlemaps import GoogleMaps
from flask_googlemaps import Map

app = Flask(__name__)


app.config['GOOGLEMAPS_KEY'] = "AIzaSyAVeBrdyRkzpXTR6MxIl1BBRy_iDcIT9_Q"
GoogleMaps(app)

from app import views
