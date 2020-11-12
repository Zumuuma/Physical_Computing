window.onload = Main;

const base_url = "https://api.thingspeak.com/channels/1225088/feeds.json";
const api_key = "0PNGGPVT4PU6H5K8";

let app;

function Main() {
	app = new Vue({
		el: "#app",
		data: {
			labels: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],   // x���̃��x��
			datasets: [  // �O���t���ƂɃI�u�W�F�N�g���`����
				{
					label: "CdS_Value",
					data: [],
					borderWidth: 5,    // ���̑���
					borderColor: "rgba(255, 20, 147, 0.5)",    // �s���N�̐F
					fill: false   // ���̉��̗̈�h��ׂ��Ȃ�
				}
			]
		},
		mounted: function () {
			updateData();
			setInterval(updateData, 15000);
		}
	});
}

function updateData() {
	const result_num = 10;
	let url = base_url +
		"?api_key=" +
		api_key +
		"&timezone=Asia/Tokyo" +
		"&results=" +
		result_num;
	fetch(url, { method: 'GET' })
		.then(function (response) {
			return response.json();
		})
		.then(function (res) {
			let brightness = [];
			res.feeds.forEach(elm => {
				brightness.push(elm.field1);
			});
			app.datasets[0].data = brightness;

			console.log(app.datasets[0].data);

			exeCreateChart();
		});
}

function exeCreateChart() {
	let ctx = document.getElementById("myChart");    // �`��̈��Canvas���擾
	let myChart = new Chart(ctx, {   // Chart�I�u�W�F�N�g�̐���
		type: "line",
		data: {
			labels: app.labels,    // x���̃��x��
			datasets: app.datasets
		},
		options: {
			responsive: true
		}
	})
}