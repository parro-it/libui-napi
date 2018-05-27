import {start, ui} from '../../../js/fancy-api.js';

start(() => {
	const win = (<window title='Control Gallery' width={800} height={600} margined={true}>
		<tab>
			<vbox label='Basic Controls'>
				{basicControlsPage}
			</vbox>
			<vbox label="Numbers and Lists">
				{numbersPage}
			</vbox>
			<vbox label='Data Choosers'>
				{dataChoosersPage}
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

const numbersPage = (
	<hbox padded>
		<group margined stretchy title='Numbers'>
			<spinbox min={0} max={100}/>
			<slider min={0} max={
		100}/>
			<progressbar value={42}/>
			<progressbar value={
		-1}/>
		</group>
		<group stretchy margined title='Lists'>
			<combobox items={
		['Combobox Item 1', 'Combobox Item 2', 'Combobox Item 3']}/>

			<editcombo items={[
				"Editable Item 1",
				"Editable Item 2",
				"Editable Item 3"]}/>

			<radio items={
		['Radio Item 1', 'Radio Item 2', 'Radio Item 3']}/>
		</group>

	</hbox>
);

const dataChoosersPage = null