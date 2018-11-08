const libui = require('..');
const {Text, Image, Checkbox, ProgressBar, Button} = libui.UiTableModel.Fields;

const win = new libui.UiWindow('Tables example', 800, 600, true);
win.margined = true;

const model = libui.UiTableModel.fromMetadata({
	name: {type: Text, editable: true, header: 'Name'},
	surname: {type: Text},
	male: {type: Checkbox, editable: true, header: 'Is a male?'},
	picture: {type: Image, value: () => img},
	completed: {type: ProgressBar},
	sayhi: {
		type: Button,
		editable: () => 1,
		label: 'Say Hi',
		click: obj => libui.UiDialogs.msgBox(win, 'HI', obj.name + ' ' + obj.surname)
	}
});

const data = [
	{name: 'Andrea', surname: 'Parodi', male: true, completed: 30},
	{name: 'Giorgia', surname: 'Parodi', male: false, completed: 75}
];

const tb = new libui.UiTable(model.bind(data));
model.addColumns(tb, 'name', 'surname', 'picture', 'male', 'completed', 'sayhi');

const vbox = new libui.UiVerticalBox();
vbox.append(tb, true);
win.setChild(vbox);

win.onClosing(() => {
	win.close();
	libui.stopLoop();
});

let img = null;
async function run() {
	img = await libui.UiImage.loadFromPng(__dirname + '/lightning-orb.png');
	win.show();
	libui.startLoop();
}

run().catch(err => console.error(err));
