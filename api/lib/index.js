// main file 

const { getAPI } = require('./time');
const { getRTC } = require('./time');
const { parseJSON } = require('./time');

async function time() {
    try {
        time = await getAPI();
        parseJSON(time);
    } catch (error) {
        time = await getRTC();
        parseJSON(time);
    }
}

time();