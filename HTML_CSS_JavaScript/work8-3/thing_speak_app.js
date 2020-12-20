window.onload = Main;

const base_url = "https://api.thingspeak.com/channels/1225088/feeds.json";
const api_key = "API_KEY"

let app;

function Main() {
	app = new Vue({
		el: "#app",
		data: {
			createdAt: [],
			brightness: []
		},
		mounted: function (event) {
			updateData()
			setInterval(updateData, 15000);
		}
	});
}


function updateData() {
	const result_num = 5
	let url = base_url +
		"?api_key=" +
		api_key +
		"&timezone=Asia/Tokyo" +
		"&results=" +
		result_num
	fetch(url, { method: 'GET' })
		.then(function (response) {
			return response.json();
		})
		.then(function (res) {
			// console.log(res.feeds);
			let createdAt = []
			let brightness = []
			res.feeds.forEach(elm => {
				createdAt.push(elm.created_at);
				brightness.push(elm.field1);
			});
			app.createdAt = createdAt;
			app.brightness = brightness;
		});
}