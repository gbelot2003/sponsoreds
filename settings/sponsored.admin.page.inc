<?php 

/**
 * Implement page callback
 */

function admin_config_sponsored(){
	return drupal_get_form('sponsored_setting_form');
} 

/**
 *  Creating menu response
 */

function sponsored_setting_form($form, &$form_state){

	if($image_fid = variable_get('image', FALSE)){
		$image = file_load($image_fid);
		$style = variable_get('image_style_name', 'thumbnail');
		$form['image'] = array(
			'#markup' => theme('image', array('image' => $image, 'style' => $style)),
		);
	}

	$form['modes'] = array(
		'#type' => 'fieldset',
		'#title' => t('Sponsoreds List Images'),
		'#collapsoble' => TRUE,
		'#collapsed' => FALSE,
		'#tree' => TRUE
	);

	$form['modes']['images_style'] = array(
		'#title' => t('Image Style'),
		'#type' => 'select',
		'#description' => t('Choose an image style to ise when displaying this image.'),
		'#options' => image_style_options(TRUE),
		'#default_value' => variable_get('image_style_name', ''),
	);

	$form['modes']['images'] = array(
	  '#title' => t('Image'),
	  '#type' => 'managed_file',
	  '#description' => t('The uploaded image will be displayed on this page using the image style choosen below.'),
	  '#default_value' => variable_get('images', ''),
	  '#upload_location' => 'public://sponsored_images/',
	);

	 // Submit Button.
    $form['submit'] = array(
    	'#type' => 'submit',
    	'#value' => t('Save'),
  	);

	return $form;
}

/**
 *  Setting submit form state
 *  sponsorted_setting_form_sumbit
 */

function sponsored_setting_form_submit($form, &$form_state){

	if($form_state['values']['modes']['images'] != 0){
		$file = file_load($form_state['values']['modes']['images']);
		$file->status = FILE_STATUS_PERMANENT;
		file_save($file);
		file_usage_add($file, 'images', 'sponsored_image', 1); //"sponsored_image" this is the way we refer when bring up the files from db
		variable_set('images', $file->fid);

		drupal_set_message(t('The image @image_name was uploaded and saved with an ID of @fid and will be displayed using the style @style.', array(
	      '@image_name' => $file->filename,
	      '@fid' => $file->fid,
	      '@style' => $form_state['values']['modes']['images_style'],
	    )));

	} 
	elseif($form_state['values']['modes']['images'] == 0) {
		$fid = variable_get('images', FALSE);
		$file = $fid ? file_load($fid) : FALSE;
		if ($file) {
			file_usage_delete($file, 'images', 'sponsored_image', 1);
			file_delete($file);
		}
		 variable_set('images', FALSE);
		 drupal_set_message(t('The images @image_name was removed.', array('@image_name' => $file->filename)));
	}
	// Save the name of the image style choosen by the user.
  	variable_set('images', $form_state['values']['modes']['images_style']);
}

function sponsored_setting_form_validate($form, &$form_state){
	if (!isset($form_state['values']['modes']['images']) || !is_numeric($form_state['values']['modes']['images'])){
		form_set_error('images', t('Please select an image to upload'));
	} 
}