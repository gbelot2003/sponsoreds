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

function sponsored_setting_form(){
	$form = array();

	$form['modes'] = array(
		'#type' => 'fieldset',
		'#title' => t('Sponsoreds List Images'),
		'#collapsoble' => TRUE,
		'#collapsed' => FALSE,
		'#tree' => TRUE
	);

	$form['modes']['images'] = array(
		'#type' => 'textfield',
		'#title' => t('Test Fields'),
		'#description' => t('Test for Forms output'),
	);

	return $form;
}