from time import sleep
from adc_8chan_12bit import Pi_hat_adc
from flask import Flask, render_template

adc = Pi_hat_adc()
app = Flask(__name__)


@app.route('/')
def root_page():
    brightness = adc.get_nchan_adc_raw_data(0)
    return render_template('index.html', brightness=brightness)


if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=8888, threaded=True)
