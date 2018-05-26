import {start, ui} from '../../../js/fancy-api.js';

start(() => {
	const win = (<window title='Control Gallery' width={800} height={600} margined={true}>
		<tab>
			<vbox label='Basic Controls'>
				{basicControlsPage}
			</vbox>
			<vbox label="Numbers and Lists">
				{makeNumbersPage()}
			</vbox>
			<vbox label='Data Choosers'>
				{makeDataChoosersPage()}
			</vbox>
		</tab>
	</window>);
	return win;
});

const basicControlsPage = (
	<vbox padded>
		<hbox padded>
			<button text="Button"/>
			<checkbox text='Checkbox'/>
		</hbox>
		<label>
			This is a label. Right now,
			labels can only span one line.
		</label>
		<hseparator/>
		<group title='Entries' margined stretchy>
			<form padded stretchy>
				<entry label='Entry' />
				<password label='Password Entry'/>
				<search label='Search Entry'/>
				<textarea label='Wrapped Multiline Entry' stretchy wrapped></textarea>
				<textarea label="Multiline Entry" stretchy></textarea>
			</form>
		</group>
	</vbox>
);

function makeDataChoosersPage() {
	return null;
}
function makeNumbersPage() {
	return null;
}