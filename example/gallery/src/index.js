import {start, ui} from '../../../js/fancy-api.js';

start(() => {
	const win =
		(<window title = 'Control Gallery' width = {800} height = {600} margined = {true}>
		 <h - box><text - area id = 'entry' onChanged = {
			 () => {
				 win.logEntry.append(`Text changed to ${win.entry.text}\n`);
			 }
		 }>A test line<br />A second test line</text-area>

			<text-area id="logEntry"/>
		 </h-box>
	</window>);
	return win;
});
