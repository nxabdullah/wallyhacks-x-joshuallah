from flask import Flask, jsonify, send_file

app = Flask(__name__)

# A sample hashmap mapping bus stop numbers to the bus routes that serve them.
bus_stop_routes = {
    "0001": ["13"],
    "0002": ["13"],
    "0003": [],            # Inactive or no routes
    "0004": ["34", "35"],
    "0005": [],            # Inactive
    "0006": [],            # Inactive
    "0007": [],            # Inactive
    "0008": [],            # Inactive
    "0009": ["26", "29", "36"],
    "0010": ["74"],
    "0011": ["66"],
    "0012": ["7", "74"],
    "0014": ["7", "39", "43"]
}

def get_routes(bus_stop_number):
    """
    Return the list of bus routes for the given bus stop number.
    
    Parameters:
        bus_stop_number (str): The bus stop number (e.g., "0001").
    
    Returns:
        list: A list of route numbers serving the bus stop.
    """
    return bus_stop_routes.get(bus_stop_number, [])


@app.route('/bus_timing')
def bus_timing():

    #stop_number = request.args.get('stop')


    # Simulate bus timing information.
    return jsonify({
        'bus_number': '42',
        'arrival_time': '5 mins',
        'destination': 'Downtown'
    })

@app.route('/audio')
def audio():
    # Return a sample audio file (make sure to have 'audio.mp3' in your project folder).
    return send_file('audio.mp3', mimetype='audio/mpeg')

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
